#include "s21_graph/s21_graph.h"
#include "s21_graph/s21_graph_algorithms.h"

void printArray(int *arr, int size)
{
  for (int i = 0; i < size; ++i)
  	std::cout << arr[i] << " ";
  std::cout << std::endl;
}

int main()
{
  Graph graph;
  graph.loadGraphFromFile(FILENAME);
  int *array = GraphAlgorithms::depthFirstSearch(graph, 1);
  printArray(array, graph.getVerticesNumber());
//  graph.exportGraphToDot(DOTFILENAME);
}
