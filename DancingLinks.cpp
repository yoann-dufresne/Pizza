#include <stdlib.h>
#include <iostream>

#include "DancingLinks.h"



struct element_s {
	int val;
	element_s * left;
	element_s * right;
	element_s * top;
	element_s * bottom;
};
typedef struct element_s element_t;

element_t * first_head;
element_t * header;
element_t * elements;


DancingLinks::DancingLinks (int nbElements, vector<Tile> tiles) {
	// Header creation
	header = (element_t *) malloc (nbElements * sizeof (element_t));
	for (int i=0 ; i<nbElements ; i++) {
		header[i].val = 0;
		header[i].top = header + i;
		header[i].bottom = header + i;
		header[i].left = header + ((nbElements+i-1)%nbElements);
		header[i].right = header + ((i+1)%nbElements);
	}
	first_head = header;


	// Count and create structure for the elements in the sparse matrix
	int nbMatrixElements = 0;
	for (Tile & tile : tiles) {
		nbMatrixElements += tile.values.size();
	}
	elements = (element_t *) malloc (nbMatrixElements * sizeof(element_t));
	int nextId = 0;

	// cout << "number of elements in the matrix: " << nbMatrixElements;
	// cout << " (" << (nbElements*sizeof(element_t)/1024) << "Ko)" << endl;


	// filling the matrix
	int tileId = 1;
	for (Tile & tile : tiles) {
		int position = 0;
		int maxPos = tile.values.size() - 1;

		for (int elem : tile.values) {
			elements[nextId].val = -tileId;

			// Point the correct elements in the new element
			elements[nextId].bottom = header[elem].bottom;
			elements[nextId].top = header + elem;

			//cout << nextId << ' ' << elements[nextId].val << ' ' << elem << endl;
			//cout << elements[nextId].bottom->top << ' ' << elements[nextId].top->bottom << endl;

			// Insert in the list
			elements[nextId].bottom->top = elements + nextId;
			elements[nextId].top->bottom = elements + nextId;

			// Update the header count
			header[elem].val += 1;

			//cout << elements[nextId].bottom->top << ' ' << elements[nextId].top->bottom << endl;

			// Add left and right
			if (position != 0)
				elements[nextId].left = elements + nextId - 1;
			else
				elements[nextId].left = elements + nextId + maxPos;

			if (position != maxPos)
				elements[nextId].right = elements + nextId + 1;
			else
				elements[nextId].right = elements + nextId - maxPos;

			//cout << elements[nextId].left << ' ' << elements[nextId].right << endl;

			++nextId;
			++position;
		}
		tileId++;
	}
}

DancingLinks::~DancingLinks () {
	free (header);
	free (elements);
}


int colLen (element_t * elem) {
	element_t * current = elem->bottom;
	
	int nb = 0;
	while (current != elem) {
		nb += 1;
		current = current->bottom;
	}

	return nb;
}


void updateHeader (element_t * colElem, int val) {
	element_t * current = colElem->top;
	while (current->val < 0) // BUG BUG BUG 0 : part numéro 0
		current = current->top;
	current->val += val;
}


// /!\ Don't use it on header elements !
void removePartAdded (element_t * elem) {
	// For all the elements in the line of interest get all the columns
	element_t * lineElem = elem;

	do {
		// For all the elements in the colums : go for delete the row
		element_t * colElem = lineElem->bottom;
		
		while (colElem != lineElem) {
			// If header
			if (colElem->val >= 0) {
				// Move the first head if the current head is this one
				if (first_head == colElem) {
					if (first_head->right == first_head)
						first_head = NULL;
					else
						first_head = first_head->right;
				}

				// Remove the head from the linked list
				colElem->right->left = colElem->left;
				colElem->left->right = colElem->right;

				colElem->val -= colLen(colElem);

			} else {
				element_t * removedLine = colElem->right;

				while (removedLine != colElem) {
					// Remove the element
					removedLine->top->bottom = removedLine->bottom;
					removedLine->bottom->top = removedLine->top;

					// update the column value
					updateHeader(removedLine, -1);

					// Go to the next element
					removedLine = removedLine->right;
				}
			}

			colElem = colElem->bottom;
		}

		lineElem = lineElem->right;
	} while (lineElem != elem);
}

void restorePartAdded (element_t * elem) {
	// For all the elements in the line of interest get all the columns
	element_t * lineElem = elem;

	do {

		// For all the elements in the colums : go for restore the row
		element_t * colElem = lineElem->bottom;
		
		while (colElem != lineElem) {
			// If header
			if (colElem->val >= 0) {
				// Restore the head from the linked list
				colElem->right->left = colElem;
				colElem->left->right = colElem;

				colElem->val += colLen(colElem);

			} else {
				element_t * removedLine = colElem->right;

				while (removedLine != colElem) {
					// Restore the element
					removedLine->top->bottom = removedLine;
					removedLine->bottom->top = removedLine;

					// update the column value
					updateHeader(removedLine, 1);

					// Go to the next element
					removedLine = removedLine->right;
				}
			}

			colElem = colElem->bottom;
		}

		lineElem = lineElem->right;
	} while (lineElem != elem);
}

int countHeads () {
	if (first_head == NULL)
		return 0;

	int nb = 0;
	element_t * current = first_head;
	do {
		nb += 1;

		current = current->right;
	} while (current != first_head);

	return nb;
}






// ======================= Solve =======================

element_t * getMinHead ();
bool recurSolve (vector<int> & solution, int errors);


element_t * getMinHead () {
	//cout << "getMinHead" << endl;
	element_t * current = first_head;

	int min = first_head->left->val;
	element_t * minElem = current->left;

	while (current->right != first_head) {
		if (current->val == 0)
			return current;

		if (current->val < min) {
			min = current->val;
			minElem = current;
		}

		current = current->right;
	}

	return minElem;
}

bool recurSolve (vector<int> & solution, int errors) {
	//cout << "recurSolve\t" << errors << endl;
	if (first_head == NULL)
		return true;

	element_t * minElem = getMinHead ();
	//cout << minElem->val << '\t' << countHeads() << endl;

	// In case of no further possibilities without errors
	if (minElem->val == 0) {
		if (errors == 0)
			return false;
		else {
			minElem->right->left = minElem->left;
			minElem->left->right = minElem->right;

			if (first_head == minElem) {
				if (minElem != minElem->right)
					first_head = minElem->right;
				else
					first_head = NULL;
			}

			if (recurSolve(solution, errors-1))
				return true;

			minElem->right->left = minElem;
			minElem->left->right = minElem;
			return false;
		}
	}

	//removePartAdded(minElem->bottom);
	//restorePartAdded(minElem->bottom);
	// Test for all the possible parts avaible for the min column
	element_t * current = minElem->bottom;
	while (current != minElem) {
		// Add the part to the solution
		removePartAdded(current);
		solution.push_back(0-(current->val));
		//cout << "\tpushed: " << (0-current->val) << endl;
		
		// Recursive search
		if (recurSolve(solution, errors))
			return true;

		// Restore the previous solution
		//cout << "\tpoped: " << (0-current->val) << endl;
		solution.pop_back();
		restorePartAdded(current);

		current = current-> bottom;
	}

	return false;
}


vector<int> DancingLinks::solve (int errors) {
	vector<int> solution;

	recurSolve (solution, errors);

	// /!\ Tiles ids = real_position + 1;
	// cout << solution.size() << endl;
	// for (int val : solution)
	// 	cout << val << ' ';
	// cout << endl;

	return solution;
}













