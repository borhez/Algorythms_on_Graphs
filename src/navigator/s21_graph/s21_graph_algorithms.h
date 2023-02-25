#ifndef NAVIGATOR_SRC_GRAPHALGORITHMS_H_
#define NAVIGATOR_SRC_GRAPHALGORITHMS_H_

#include <vector>
#include <limits>
#include "s21_graph.h"
#include "../stack/Stack.hpp"

struct TsmResult {
    std::vector<int> vertices;// an array with the route you are looking for (with the vertex traverse order). Instead of int* you can use std::vector<int>
    double distance;  // the length of this route
};


class GraphAlgorithms
{
public:
  static std::vector<int> depthFirstSearch(Graph &graph, int startVertex);

  // до vertex2 можно и не дойти до vertex2
  static double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  static std::vector<std::vector<double>> getShortestPathsBetweenAllVertices(Graph &graph);
  static std::vector<std::vector<int>> getLeastSpanningTree(Graph &graph);
  static TsmResult solveTravelingSalesmanProblem(Graph &graph);
  //без static, в main(): нестатическая ссылка не член должна указываться относительно заданного объекта
};


#endif // NAVIGATOR_SRC_GRAPHALGORITHMS_H_
