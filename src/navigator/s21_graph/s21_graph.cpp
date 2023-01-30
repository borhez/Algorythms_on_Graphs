#include "s21_graph.h"

int Graph::loadGraphFromFile(const std::string &filename) {
  std::ifstream fin;
  fin.open(filename, std::ios::in);
  if(!fin.is_open() || fin.bad())
	return error("loadFile error");

  std::string line;
  std::getline(fin, line);
  std::size_t size = std::stoi(line);
  delete _m;
  _m = new Matrix(size);

  char *pStart;
  std::size_t pEnd;
  int inCol, inRow = -1;
  while (std::getline(fin, line) && ++inRow < size)
  {
	inCol = 0;
	pStart = &(line[0]);
	do
	{
	  try
	  {
	  _m->at(inRow, inCol) = std::stoi(pStart, &pEnd);
	  }
	  catch (std::exception &e)
	  {
		return error(e.what());
	  }
	  if (_m->at(inRow, inCol) < 0)
		return error("negative distance");
	  pStart += pEnd;
	}while (*pStart && ++inCol < size);
	if (inCol != size - 1)
	   return error("wrong columns number");
  }
  if (inRow != size - 1)
  	return error("wrong rows number");
  fin.close();
  return 1;
}
int Graph::exportGraphToDot(const std::string &filename) {
  std::ofstream fout;
  fout.open(filename, std::ios::out | std::ios::trunc);
  if(!fout.is_open() || fout.bad())
	 return error("exportFile error");

  // Очень спорно и непонятно!!!
  fout << "graph graphname {" << std::endl;
  for (int i = 0; i < _m->getSideSize(); ++i)
	fout << i + 1 << ";" << std::endl;
  //

  for (int r = 0; r < _m->getSideSize(); ++r)
  {
	for (int c = 0; c < _m->getSideSize(); ++c)
	{
	  if (c == r) continue;
	  fout << r + 1 << " -- " << c + 1 << " [label="
	  << _m->at(r,c) << "];" << std::endl;
	}
  }
  fout << "}";
  fout.close();
}

double Graph::getDist(size_t a, size_t b) {
  if (a >= _m->getSideSize() || b >= _m->getSideSize())
	throw std::out_of_range("wrong vertices number");
  return _m->at(a, b);
}

int error(const std::string &massage){
  std::cout << massage << std::endl;
  return -1;
}
