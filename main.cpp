#include <iostream>
#include <vector>

#include "Problem.h"
#include "Solution.h"
#include "HillClimbing.h"


int main () {
	int rows, cols, min, max;
	cin >> rows >> cols >> min >> max;

	Problem prob (rows, cols, min, max);
	prob.generateSlices ();

	Solution sol (prob);
	sol.randomSolution();
	//cout << "Score: " << sol.score << endl;
	
	HillClimbing hc = HillClimbing(sol);
	for (int i=0 ; i<100000 ; i++) {
		cout << "Improvement: " << hc.oneStep(100) << endl;
		cout << "Score: " << hc.sol.score << endl;
	}

	return 0;
}
