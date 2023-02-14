#ifndef NAVIGATOR_SRC_GRAPHALGORITHMS_H_
#define NAVIGATOR_SRC_GRAPHALGORITHMS_H_

#include <vector>
#include <limits>
#include "s21_graph.h"
#include "../stack/Stack.hpp"

class GraphAlgorithms {
 public:
  static std::vector<int> depthFirstSearch(Graph &graph, int startVertex);

  // до vertex2 можно и не дойти до vertex2
  static double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  static std::vector<std::vector<double>> getShortestPathsBetweenAllVertices(Graph &graph);
  static int *getLeastSpanningTree(Graph &graph);
};

#endif //NAVIGATOR_SRC_GRAPHALGORITHMS_H_
