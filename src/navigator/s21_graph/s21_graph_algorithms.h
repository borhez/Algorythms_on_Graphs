#ifndef NAVIGATOR_SRC_GRAPHALGORITHMS_H_
#define NAVIGATOR_SRC_GRAPHALGORITHMS_H_

#include <vector>
#include "s21_graph.h"
#include "../stack/Stack.hpp"

class GraphAlgorithms {
 public:
  static int * depthFirstSearch(Graph &graph, int startVertex);
};

#endif //NAVIGATOR_SRC_GRAPHALGORITHMS_H_
