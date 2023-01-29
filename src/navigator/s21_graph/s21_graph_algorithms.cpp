#include "s21_graph_algorithms.h"
int *GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  int iRes = 0;
  auto *res = new int[graph.getVerticesNumber()];
  Stack<int> stack;
  std::vector<int> visited(graph.getVerticesNumber(), 0);
  stack.init();

  stack.push(startVertex - 1);
  visited[stack.peek()] = 1;
  res[iRes++] = stack.peek() + 1;
  while (stack.GetSize() > 0) // прерывестый граф
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
	  if (c == graph.getVerticesNumber() - 1) // пункт больше никуда не ведет
	  {
		for (int r = 0; r < graph.getVerticesNumber(); ++r) // може что-то ведет в пункт
		{
		  if (graph.getDist(r, stack.peek()) != 0 && visited[r] == 0) {
			visited[r] = 1;
			res[iRes++] = r + 1;
			stack.push(r);
			break;
		  }
		  if (r == graph.getVerticesNumber() - 1)
		  	stack.pop();
		}
	  }
	}
	if (stack.GetSize() == 0 && iRes < graph.getVerticesNumber())// для разделенного графа
	{
	  stack.push(std::find(visited.begin(), visited.end(), 0) - visited.begin());
	  visited[stack.peek()] = 1;
	  res[iRes++] = stack.peek() + 1;
	}
  }
  return res;
}
