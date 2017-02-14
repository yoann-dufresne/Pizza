#include "Problem.h"
#include "Solution.h"

#ifndef HILL_H
#define HILL_H

using namespace std;

class HillClimbing {
public:
	Solution sol;
	vector<Slice> order;

	HillClimbing (Solution & sol);
	int oneStep (int nMutations);
};

#endif
