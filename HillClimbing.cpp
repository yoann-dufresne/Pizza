#include "HillClimbing.h"


int myrandom2 (int i) {return rand() % i;}

HillClimbing::HillClimbing (Solution & sol) {
	this->sol = Solution(sol.prob);

	this->order = sol.prob.slices;

	srand(time(0));
	random_shuffle(this->order.begin(), this->order.end(), myrandom2);

	for (Slice & slc: this->order) {
		this->sol.addSlice (slc);
	}
	cout << "Initial score: " << this->sol.score << endl;
}

int HillClimbing::oneStep (int nbMut) {
	Solution sol (this->sol.prob);
	vector<Slice> newOrder = this->order;

	for (int i=0 ; i<nbMut ; i++) {
		int idx = rand() % newOrder.size();
		Slice & slc = newOrder[idx];
		newOrder.erase(newOrder.begin() + idx);

		idx = rand() % newOrder.size();
		newOrder.insert(newOrder.begin()+idx, slc);
	}

	for (Slice & slc : newOrder)
		sol.addSlice(slc);

	if (sol.score - this->sol.score >= 0) {
		this->sol = sol;
		this->order = newOrder;
	}

	return sol.score - this->sol.score;
}
