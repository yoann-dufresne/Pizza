#include "Solution.h"


Solution::Solution () {}

Solution::Solution (Problem prob) {
	this->prob = prob;
	this->coverage = vector<vector<bool> > (prob.rows, vector<bool> (prob.cols, false));
	this->score = 0;
}

int myrandom (int i) {return rand() % i;}

void Solution::randomSolution () {
	srand(time(0));

	vector<Slice> slices = prob.slices;
	random_shuffle(slices.begin(), slices.end(), myrandom);

	for (Slice & slc: slices) {
		this->addSlice (slc);
	}
}

bool Solution::addSlice (Slice & slc) {
	for (int r=slc.r1 ; r<=slc.r2 ; r++) {
		for (int c=slc.c1 ; c<=slc.c2 ; c++) {
			if (this->coverage[r][c])
				return false;
		}
	}

	for (int r=slc.r1 ; r<=slc.r2 ; r++) {
		for (int c=slc.c1 ; c<=slc.c2 ; c++) {
			this->coverage[r][c] = true;
		}
	}

	this->score += (slc.r2 - slc.r1 + 1) * (slc.c2 - slc.c1 + 1);
	this->slices.push_back(slc);

	return true;
}
