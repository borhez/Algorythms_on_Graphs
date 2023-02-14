#ifndef NAVIGATOR_S21_GRAPH_H
#define NAVIGATOR_S21_GRAPH_H

#include <string>
#include <fstream>
#include <iostream>
#include "../matrix/Matrix.hpp"

#define UNDIRECT 	0
#define DIRECT 		1

#define FILENAME "complex_test.txt"
#define DOTFILENAME "complex_test.dot"

class Graph {
private:
    Matrix *_m;
	int _type = UNDIRECT;
public:
    ~Graph() { delete _m;}				// !!! как это тестить, если есть ток lesks?
    Graph() : _m(new Matrix(0)) {}

    int loadGraphFromFile(const std::string &filename);
    int exportGraphToDot(const std::string &filename);

	double getDist(size_t a, size_t b);
	std::size_t getVerticesNumber() { return _m->getSideSize(); }
    int getMatrxElem(int row, int col) {return _m->at(row, col);}
};

int error(const std::string &massage);

#endif //NAVIGATOR_S21_GRAPH_H
