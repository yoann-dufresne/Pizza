#include <vector>

using namespace std;

#ifndef SLICE_H
#define SLICE_H


class Slice {
public:
	int r1;
	int c1;
	int r2;
	int c2;

	Slice (int r1, int c1, int r2, int c2);

	int size ();
	void print (vector<vector<char> > pizza);
	void printVerbose (vector<vector<char> > pizza);
};

#endif
