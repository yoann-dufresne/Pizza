#include <vector>


using namespace std;

#ifndef DANCING_LINKS_H
#define DANCING_LINKS_H

class Tile {
public:
	vector<int> values;
};


class DancingLinks {
public:
	DancingLinks (int nbElements, vector<Tile> tiles);
	~DancingLinks ();

	vector<int> solve (int errors);
};

#endif
