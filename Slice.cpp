#include <iostream>

#include "Slice.h"


Slice::Slice (int r1, int c1, int r2, int c2) {
	this->r1 = r1;
	this->c1 = c1;
	this->r2 = r2;
	this->c2 = c2;
}

int Slice::size () {
	return (r2-r1)*(c2-c1);
}

void Slice::print (vector<vector<char> > pizza) {
	cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << ' ' << endl;
}

void Slice::printVerbose (vector<vector<char> > pizza) {
	this->print(pizza);

	for (int r=this->r1 ; r<=this->r2 ; r++) {
		for (int c=this->c1 ; c<=this->c2 ; c++) {
			if (pizza[r][c] == 0)
				cout << 'T';
			else
				cout << 'M';
		}
		cout << endl;
	}
}
