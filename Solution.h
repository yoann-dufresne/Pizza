#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Problem.h"


#ifndef SOL_H
#define SOL_H

using namespace std;

class Solution {
public:
	Problem prob;
	vector<vector<bool> > coverage;
	int score;
	vector<Slice> slices;

	Solution ();
	Solution (Problem prob);
	void randomSolution ();
	bool addSlice (Slice & slc);
};

#endif
