#include <vector>
#include <string>

#include "Slice.h"


#ifndef PIZZA_H
#define PIZZA_H

#define IDX(row, col) (row * nbCols + col)


extern int nbRows, nbCols, minHam, maxSurf;
extern vector<vector<char> > pizza;

void parse ();
vector<Slice> genereateSlices (string filename);
vector<Slice> loadSlices (string filename);
#endif
