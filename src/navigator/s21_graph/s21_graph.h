#ifndef NAVIGATOR_S21_GRAPH_H
#define NAVIGATOR_S21_GRAPH_H

#include <string>
#include <fstream>
#include <iostream>
#include "../matrix/Matrix.hpp"

#define FILENAME "test.txt"
#define DOTFILENAME "test.dot"

class Graph {
private:
    Matrix *_m;
public:
    Graph() : _m(nullptr) {}
    ~Graph() { delete _m;}

    int loadGraphFromFile(const std::string &filename);
    int exportGraphToDot(const std::string &filename);

	double getDist(size_t a, size_t b);
	std::size_t getVerticesNumber() { return _m->getSideSize(); }
};

int error(const std::string &massage);

#endif //NAVIGATOR_S21_GRAPH_H
