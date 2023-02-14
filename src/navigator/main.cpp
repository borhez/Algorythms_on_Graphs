#include "s21_graph/s21_graph.h"
#include "s21_graph/s21_graph_algorithms.h"
#include "matrix/Matrix.hpp"

// void printArray(int *arr, int size)
// {
//   for (int i = 0; i < size; ++i)
//   	std::cout << arr[i] << " ";
//   std::cout << std::endl;
// }

void printArray(std::vector<int> arr, int size)
{
  for (int i = 0; i < size; ++i)
  	std::cout << arr[i] << " ";
  std::cout << std::endl;
}


int main()
{
  Graph graph;
  printf("main:24\n");

  if (graph.loadGraphFromFile("../unit_test_files/proba1.txt") < 0)
	  return -1;
  // std::vector<int> array = GraphAlgorithms::depthFirstSearch(graph, 1);
  // printArray(array, graph.getVerticesNumber());
  // graph.exportGraphToDot("../unit_test_files/proba1.dot");

  int *mtrx_ostTree = GraphAlgorithms::getLeastSpanningTree(graph);
  return 1;
}