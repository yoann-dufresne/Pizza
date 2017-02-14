#include "Problem.h"


Problem::Problem () {};
Problem::Problem (int rows, int cols, int mins, int maxSurf) {
	this->rows = rows;
	this->cols = cols;
	this->mins = mins;
	this->maxSurf = maxSurf;

	char ch;
	this->data = vector<vector<bool> > (rows, vector<bool> (cols, false));
	for (int r=0 ; r<rows ; r++) {
		for (int c=0 ; c<cols ; c++) {
			cin >> ch;
			this->data[r][c] = ch == 'M';
		}
	}
}

Problem::~Problem () {}

void Problem::generateSlices() {
	for (int r=0 ; r<this->rows ; r++)
		for (int c=0 ; c<this->cols ; c++)
			for (int h=1 ; h<=this->maxSurf ; h++)
				for (int w=1 ; w<=this->maxSurf ; w++)
					if (h*w >= 2*this->mins && h*w <= this->maxSurf // Surface constraints
							&& r+h-1 < this->rows && c+w-1 < this->cols // Size constraints
							&& this->isRoyal(r, c, w, h)) { // Composition constraints
						this->slices.push_back(Slice(r, c, r+h-1, c+w-1));
					}

	cout << "Number of possible slices: " << this->slices.size() << endl;
}

bool Problem::isRoyal (int row, int col, int width, int height) {
	int mush=0;
	for (int r=row ; r<row+height ; r++)
		for (int c=col ; c<col+width ; c++)
			if (this->data[r][c])
				mush++;

	return mush >= this->mins && (width*height - mush) >= this->mins;
}
















