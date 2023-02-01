#include "s21_graph_algorithms.h"
std::vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex){
  int iRes = 0;
  std::vector<int> res(graph.getVerticesNumber(), 0);
  Stack<int> stack;
  std::vector<int> visited(graph.getVerticesNumber(), 0);
  stack.init();

  stack.push(startVertex - 1);
  visited[stack.peek()] = 1;		// защита от зацикленных пунктов
  res[iRes++] = stack.peek() + 1;
  while (stack.GetSize() > 0)
  {
	for (int c = 0; c < graph.getVerticesNumber(); ++c)
	{
	  if (graph.getDist(stack.peek(), c) != 0 && visited[c] == 0)
	  {
		visited[c] = 1;
		res[iRes++] = c + 1;
		stack.push(c);
		break;
	  }
	  if (c == graph.getVerticesNumber() - 1)
		stack.pop();
	}
  }
  return res;
}
double GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
  std::vector<double> paths(graph.getVerticesNumber(), std::numeric_limits<double>::infinity());

  double minDist = std::numeric_limits<double>::infinity();
  auto minEl = paths.begin();
  int cur = vertex1 - 1;
  paths[cur] = 0;
  // защита и на vertex1 == vertex2 и на отсутствие пути к вершине
  for (int finds = 0; finds < graph.getVerticesNumber() && cur != vertex2 - 1; ++finds )
  {
	for (int c = 0; c < graph.getVerticesNumber(); ++c)
	{
	  double dist = graph.getDist(cur, c);
	  if (dist == 0 || cur == c) continue;

	  paths[c] = std::min(paths[c], paths[cur] + dist);
	  if (paths[c] - *minEl < 0 || *minEl == 0) // минимум из оставшихся
	  	minEl = paths.begin() + c;
	}
	cur = minEl - paths.begin();
  }
  return paths[cur];
}
