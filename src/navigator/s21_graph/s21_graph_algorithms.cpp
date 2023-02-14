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
  std::vector<bool> visited(graph.getVerticesNumber(), false);

  auto minEl = paths.begin() + vertex1 - 1;
  int cur = vertex1 - 1;
  paths[cur] = 0;
  visited[cur] = true;

  // защита и на vertex1 == vertex2 и на отсутствие пути к вершине
  for (int finds = 0; finds < graph.getVerticesNumber() && cur != vertex2 - 1; ++finds )
  {
	for (int c = 0; c < graph.getVerticesNumber(); ++c)
	{
	  double dist = graph.getDist(cur, c);
	  if (!(dist == 0 || cur == c || visited[c]))
	  	paths[c] = std::min(paths[c], paths[cur] + dist);

	  if ((paths[c] - *minEl < 0 || *minEl == 0) && !visited[c])
	  	minEl = paths.begin() + c;
	}
	cur = minEl - paths.begin();
	minEl = paths.begin() + vertex1 - 1;
	visited[cur] = true;
  }
  if (cur == vertex2 - 1)
  	return paths[cur];
  return std::numeric_limits<double>::infinity();
}
std::vector<std::vector<double>> GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  std::size_t sideSize = graph.getVerticesNumber();
  std::vector<std::vector<double>> memo(sideSize);
  std::vector<std::vector<double>> prev(sideSize);
  for (int i = 0; i < sideSize; ++i)
  {
	memo[i].resize(sideSize);
	prev[i].resize(sideSize);
	for (int j = 0; j < sideSize; ++j)
	{
	  if (i == j)
		prev[i][j] = 0;
	  else if (graph.getDist(i,j) == 0)
		prev[i][j] = std::numeric_limits<double>::infinity();
	  else
		prev[i][j] = graph.getDist(i, j);
	}
  }

  for (int k = 1; k < sideSize; ++k)
  {
	for (int i = 0; i < sideSize; ++i)
	{
	  for (int j = 0; j < sideSize; ++j)
	  {
		  memo[i][j] = std::min(prev[i][j], prev[i][k] + prev[k][j]);
		  prev[i][j] = memo[i][j];
	  }
	}
  }
  return memo;
}

void	printGraphMatrix(Graph &graph)
{
	for (size_t i = 0; i < (graph.getVerticesNumber()); i++)
	{
		for (size_t j = 0; j < graph.getVerticesNumber(); j++)
		{
			printf("%d ", graph.getMatrxElem(i, j));
		}
		printf("\n");
	}
	
}

int *GraphAlgorithms::getLeastSpanningTree(Graph &graph)
{
	printf("getLeastSpanningTree(Graph &graph)\n");
	printf("matrix from file:\n");
	printGraphMatrix(graph);
	int *mtrxOstTree;
	return (mtrxOstTree);
}