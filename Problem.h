#include <iostream>
#include <vector>

#include "Slice.h"

#ifndef PROB_H
#define PROB_H

using namespace std;

class Problem {
	bool isRoyal (int row, int col, int width, int height);

public:
	int rows;
	int cols;
	int mins;
	int maxSurf;
	vector<vector<bool> > data;
	vector<Slice> slices;

	Problem ();
	Problem (int rows, int cols, int mins, int maxSurf);
	~Problem ();

	void generateSlices ();
};

#endif
