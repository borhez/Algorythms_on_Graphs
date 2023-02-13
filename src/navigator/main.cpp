#include "s21_graph/s21_graph.h"
#include "s21_graph/s21_graph_algorithms.h"

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
  // if (graph.loadGraphFromFile(FILENAME) < 0)
  if (graph.loadGraphFromFile("../unit_test_files/digraph.txt") < 0)
	  return -1;
  std::vector<int> array = GraphAlgorithms::depthFirstSearch(graph, 1);
  // int *array = GraphAlgorithms::depthFirstSearch(graph, 1);
  printArray(array, graph.getVerticesNumber());
  // graph.exportGraphToDot(DOTFILENAME);
  graph.exportGraphToDot("../unit_test_files/digraph.dot");
  return 1;
}