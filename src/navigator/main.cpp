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

void	printGraphMatrix(Graph &graph)
{
	for (size_t i = 0; i < (graph.getVerticesNumber()); i++)
	{
		for (size_t j = 0; j < graph.getVerticesNumber(); j++)
		{
			printf("%f ", graph.getDist(i, j));
		}
		printf("\n");
	}
}

static void printMatrixVector(std::vector<std::vector<int>>& mtrx, size_t size)
{
  printf("Ostov_Tree_Matrix\n");
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			printf("%d ", mtrx[i][j]);
		}
		printf("\n");
	}
}

void printTsmRes(TsmResult &tsm)
{
	printf("Way:");
	for (size_t i = 0; i < tsm.vertices.size(); i++)
	{
		printf(" %d", tsm.vertices[i]);
	}
	printf("\n");
	printf("Distance= %f\n", tsm.distance);
}

int main()
{
  Graph graph;
  

  if (graph.loadGraphFromFile("../unit_test_files/saleman21.txt") < 0)
	  return -1;
//   printf("matrix from file:\n\n");
//   printGraphMatrix(graph);
//   std::vector<int> array = GraphAlgorithms::depthFirstSearch(graph, 1);
//   printArray(array, graph.getVerticesNumber());
//   graph.exportGraphToDot("../unit_test_files/proba1.dot");

//   std::vector<std::vector<int>> mtrxOstTree = GraphAlgorithms::getLeastSpanningTree(graph);
//   printMatrixVector(mtrxOstTree, graph.getVerticesNumber());
  
  TsmResult tsm;
  tsm = GraphAlgorithms::solveTravelingSalesmanProblem(graph);
extern bool g_errorGraphTsm;
	if (g_errorGraphTsm == 0)
		printTsmRes(tsm);
	return 1;
}