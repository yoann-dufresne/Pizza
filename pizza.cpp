#include <iostream>
#include <fstream>
#include <string>

#include "pizza.h"


using namespace std;

int nbRows, nbCols, minHam, maxSurf;
vector<vector<char> > pizza;

void parse () {
	cin >> nbRows >> nbCols >> minHam >> maxSurf;
	string line;
	getline(cin, line);

	vector<vector<char> > tmp ( nbRows, vector<char> (nbCols, 0));
	pizza = tmp;

	for (int i=0 ; i<nbRows ; i++) {
		getline(cin, line);

		for (int j=0 ; j<nbCols ; j++)
			pizza[i][j] = line[j] == 'M' ? 1 : 0;
	}
}


vector<Slice> genereateSlices (string filename) {
	vector<Slice> parts;

	// For all the tiles
	for (int r=0 ; r<nbRows ; r++) {
		for (int c=0 ; c<nbCols ; c++) {

			// For all the possible parts
			for (int x=1 ; x<=maxSurf ; x++) {
				for (int y=1 ; y<=maxSurf ; y++) {
					// check the slice area
					if (x*y < minHam*2)
						continue;

					if (x*y > maxSurf)
						break;

					// Check the pizza limits
					if (c+x-1 >= nbCols || r+y-1 >= nbRows)
						continue;

					Slice slc (r, c, r+y-1, c+x-1);
					if (slc.isRoyal(pizza, minHam)) {
						parts.push_back(slc);
					}
				}
			}
		}
	}

	return parts;
}


vector<Slice> loadSlices (string filename) {
	vector<Slice> slices;
	int nb = 0;

	ifstream file(filename);
	file >> nb;
	for (int i=0 ; i<nb ; i++) {
		int r1, r2, c1, c2;
		file >> r1 >> c1 >> r2 >> c2;
		slices.push_back(Slice(r1, c1, r2, c2));
	}
	file.close ();

	return slices;
}


int verifyScore (vector<Slice> slices) {
	vector<vector<bool> > coverage (nbRows, (nbCols, false));

	int score = 0;
	for (Slice & slc : slices) {
		int nbHams = 0;

		for (int r=slc.r1 ; r<=slc.r2 ; r++) {
			for (int c=slc.c1 ; c<=slc.c2 ; c++) {
				if (coverage[r][c]) {
					return -1;
				}

				if (pizza[r][c] == 1)
					nbHams += 1;

				coverage[r][c] = true;
			}
		}

		if (nbHams < minHam)
			return -1;

		score += slice.size();
	}

	return score;
}


// void greedy_naive () {
// 	for (int i=0 ; i<nbRows ; i++)
// 		for (int j=0 ; j<nbCols ; j++) {
// 			int nbHams = 0;

// 			int end = nbCols-j < maxSurf ? nbCols-j : maxSurf;
// 			for (int s=0 ; s<end ; s++)
// 				if (pizza[i][j+s])
// 					nbHams++;

// 			if (nbHams >= minHam) {
// 				cout << i << ' ' << j << ' ' << i << ' ' << (j+end-1) << endl;
// 				j += maxSurf-1;
// 			}
// 		}
// }


