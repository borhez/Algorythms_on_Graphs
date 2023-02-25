#include "s21_graph_algorithms.h"
#include <algorithm>
#include <cmath>
#include <cassert>

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


// void fillHelpMatrix(std::vector<std::vector<int>>& helpMatrix, Graph graph, size_t nVertices)
// {
// 	for (size_t i = 0; i < nVertices; i++)
// 	{
// 		for (size_t j = 0; j < nVertices; j++)
// 		{
// 			helpMatrix[i][j] = graph.getMatrxElem(i, j);
// 		}
// 	}
// }

// void printMatrix2dVector(std::vector<std::vector<int>>& mtrx, size_t size)
// {
// 	for (size_t i = 0; i < size; i++)
// 	{
// 		for (size_t j = 0; j < size; j++)
// 		{
// 			printf("%d ", mtrx[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");
// }

// void printVectorElements(std::vector<int>& vec)
// {
// 	printf("Vector:");
// 	for (size_t i=0; i < vec.size(); i++)
// 	{
// 		printf("%d ", vec.at(i));
// 	}
// 	printf("\n\n");
// }

template <typename T>
void remove(std::vector<T>& v, size_t index)
{
    v.erase(v.begin() + index);
}

int	findStartVert(std::vector<std::vector<int>>& helpMatrix, size_t nVertices)
{
	for (size_t row = 0; row < nVertices; row++)
	{
		for (size_t col = 0; col < nVertices; col++)
		{
			if (helpMatrix[row][col] != 0)
				return row;
		}
	}
	return (-1);
}

bool checkAllElemsAreZero(std::vector<int> v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i] != 0)
			return (0);
	}
	return (1);
}


//Алгоритм Прима — алгоритм построения минимального остовного дерева взвешенного связного неориентированного графа.
std::vector<std::vector<int>> GraphAlgorithms::getLeastSpanningTree(Graph &graph)
{
	size_t nVertices = graph.getVerticesNumber();
	std::vector<std::vector<int>> mtrxOstovTree(nVertices);
	std::vector<std::vector<int>> helpMatrix(nVertices);
	
	for (size_t i = 0; i < nVertices; i++)
	{
		mtrxOstovTree[i].resize(nVertices);
		helpMatrix[i].resize(nVertices);
	}
	

	//fill matrix from graph-matrix:
	for (size_t i = 0; i < nVertices; i++)
	{
		for (size_t j = 0; j < nVertices; j++)
		{
			//Избавляюсь от петлей (зануляю диагональные элементы)
			//заполняю вспомогательную матрицу (копия загруженной из файла)
			//заполняю нулями матрицу остовного дерева
			if (i != j)
				helpMatrix[i][j] = graph.getDist(i, j);
			else { helpMatrix[i][j] = 0; }
			mtrxOstovTree[i][j] = 0;
		}
	}



	/*	2vector для хранения  вершин. На каждом шаге буду добавлять
		и убавлять вершину из этих векторов, при построении остова дерева
	*/
	// std::vector<int> unconnectedVert(nVertices);
	std::vector<int> connectedVert(0);
	// for (size_t i = 0; i < nVertices; i++)
	// {
	// 	unconnectedVert[i] = i;
	// }
	// printVectorElements(unconnectedVert);
	// printVectorElements(connectedVert);
	
	

	//ищем первую ненулевую вершину
	int startVert = findStartVert(helpMatrix, nVertices);
	// printf("%d\n", helpMatrix[startVert][3]);
	
	//удаляю стартовую вершину из unconnected, добавляю в connected
	// remove(unconnectedVert, startVert);
	connectedVert.push_back(startVert);
	// printVectorElements(unconnectedVert);



	//Search ostovTree from the 1st vertex
	//Stop search when all vertices will be connected;
	//на каждой итерации цикла добавляется одна вершина
	int tempRow, tempCol, iTemp;
	int n = 0;
	int	minWeight;
	while (n < nVertices - 1)
	{
			// printf("	Next Step!\nhelp_matrix:\n");
			// printMatrix2dVector(helpMatrix, nVertices);
			// printVectorElements(connectedVert);

		minWeight = std::numeric_limits<int>::max();
		for (size_t i = 0; i < connectedVert.size(); i++)
		{
			int row = connectedVert.at(i);
			for (size_t col = 0; col < nVertices; col++)
			{
				if ( std::find(connectedVert.begin(), connectedVert.end(), col)!=connectedVert.end())
					continue;
				if (helpMatrix[row][col] > 0 && helpMatrix[row][col] < minWeight)
				{
					minWeight = helpMatrix[row][col];
					tempRow=row;
					tempCol=col;
					iTemp = i;
				}
			}
		}
		// printf("rowTemp=%d; colTemp=%d; iTemp=%d\n", tempRow, tempCol, iTemp);
		mtrxOstovTree[tempRow][tempCol] = helpMatrix[tempRow][tempCol];
		helpMatrix[tempRow][tempCol] = 0;
		helpMatrix[tempCol][tempRow] = 0;
		// 		printf("\nafter edit, help matrix:\n");
		// printMatrix2dVector(helpMatrix, nVertices);
		// 				printf("\n TreeMatrix:\n");
		// printMatrix2dVector(mtrxOstovTree, nVertices);


		if (checkAllElemsAreZero(helpMatrix[tempRow]))
			remove(connectedVert, iTemp);
		if (!checkAllElemsAreZero(helpMatrix[tempCol]))
		 	connectedVert.push_back(tempCol);//можно оставить только эту строчку. а эти две проверки удалить
		n++;
	}
	return (mtrxOstovTree);
}

//------------------------коммивояжер-------------
	typedef struct AntStruct{
		// size_t antsMax;
		int curVert;
		int nextVert;
		std::vector<int> visited;
		std::vector<int> unvisited;
		// std::vector<size_t> path;
		// int pathIndex = -1;
		double length;
	}AntStruct;

/*
Был открыт ряд комбинаций α/β, которые позволяют находить хорошие результаты:
α/β: 0.5/5   1/1   1/2   1/5;
α ассоциируется с количеством фермента
β с видимостью (длинной грани).
Чем больше значение параметра, тем он важнее для вероятностного уравнения,
которое используется при выборе грани. В одном случае значимость параметров
равна. Во всех других случаях видимость более важна при выборе пути.

Rho (ρ): при ρ > 0,5 хорошие результаты;
		 при ρ < 0,5 неудовлетворительные.
Параметр ρ представляет коэффициент, который применяется к распыляемому
на пути ферменту, а (1,0 – ρ) представляет коэффициент испарения для
существующего фермента. 
В первую очередь этот параметр определяет концентрацию фермента,
которая сохранится на гранях.
*/
	typedef struct Data{
		double alpha = 1;//отвечает за фермент
		double beta = 5;//за расстояние
		double rho = 0.77;
		double qVal = 10;
		size_t nAnts;
		size_t nVerts;
		std::vector<std::vector<double>> pheromone;
		std::vector<int> bestWay;
		int bestDistance;
	}Data;


void checkGraph(Graph &graph)
{
	// printf("graph is not checked\n");
}

int getNextVert(AntStruct &ant, Graph &graph, Data &dataStruct)
{
		ant.curVert = *(ant.visited.end() - 1); printf("curVert: %d\n", ant.curVert);
		double denominator = 0.0;
		for (size_t unvisitInd = 0; unvisitInd < ant.unvisited.size(); unvisitInd++)
		{//для каждой непосещённой вершины считаю знаменатель:
			double distance = graph.getDist(ant.curVert, ant.unvisited[unvisitInd]);
			denominator += pow(dataStruct.pheromone[ant.curVert][ant.unvisited[unvisitInd]], dataStruct.alpha) * pow(1.0/distance, dataStruct.beta);
			// printf("pherom %lf\n", dataStruct.pheromone[ant.curVert][ant.unvisited[unvisitInd]]);
			// printf("distan %lf\n", distance);
		// printf("denom: %lf\n", denominator);
			assert(denominator != 0);
		}

		int unvisitInd = 0;
		while (1)
		{//считаю числитель и вероятность; кидаю монетку , получаю следующую вершину.
			double p, n;	
			if (unvisitInd == ant.unvisited.size())
				unvisitInd = 0;
			double distance = graph.getDist(ant.curVert, ant.unvisited[unvisitInd]);
			double nominator = pow(dataStruct.pheromone[ant.curVert][ant.unvisited[unvisitInd]], dataStruct.alpha) *\
													pow(1.0/distance, dataStruct.beta);
			// printf("\nant.unvisited[unvisitInd]=%d\n", ant.unvisited[unvisitInd]);
			// printf("nom: %lf\n", nominator);
			p = 100 * nominator / denominator;
			// printf("p=%lf\n", p);
			if ((n=rand() % 100) < p)
				{
					//printf("break; n=%lf\n", n);
					break;
				}
				// printf("n=%lf\n", n);
			unvisitInd += 1;
		}
		printf("ret=%d\n", ant.unvisited[unvisitInd]);
				// printf("denom: %lf\n\n\nnext:\n", denominator);
	int ret = ant.unvisited[unvisitInd];
	remove(ant.unvisited, unvisitInd);//ant start from curVert to nextVert
	return ret;
}
void	printVector(std::vector<int> &v)
{
	printf("\n\nbestWAY:");
	for (size_t i = 0; i < v.size(); i++)
	{
		printf(" %d",v[i]);
	}
	printf("\n\n");	
}

int antsGoGoGo(AntStruct *ants, Graph &graph, Data &dataStruct)
{
	// size_t moovingFlag = 0;
	//для каждого муравья:
	for (size_t i = 0; i < dataStruct.nAnts; i++)
	{
		printf("\n\n352:newAnt\n");
		for (; ants[i].unvisited.size() > 0;)
		{//на каждой итерации вектор unvisited уменьшается на одну вершину
		//выбрать след.вершину из вектора unvisited:
			ants[i].nextVert = getNextVert(ants[i], graph, dataStruct);
		//-----след.вершина выбрана
			ants[i].length += graph.getDist(ants[i].curVert, ants[i].nextVert);
			// printf("l=%lf\n", ants[i].length);//надо рестартить = 0
			ants[i].visited.push_back(ants[i].nextVert);//движение из curVert в nextVert
		//удаление из вектора ants[i].unvisited было в функции getNextVert()---
			// moovingFlag++;//произошло движение муравья.
		}
		//добавить начальную вершину(ants[i].visited[0]):
		ants[i].curVert = *(ants[i].visited.end() - 1);
		ants[i].length += graph.getDist(ants[i].curVert, ants[i].visited[0]);
		// printf("364:length= %lf\n", ants[i].length);
		ants[i].visited.push_back(ants[i].visited[0]);
		//---------------
		if (ants[i].length < dataStruct.bestDistance)
		{
			dataStruct.bestDistance = ants[i].length;
			//vector1.assign(vector2.begin(), vector2.end());
			dataStruct.bestWay.assign(ants[i].visited.begin(), ants[i].visited.end());
		}
	}
	// printf("finalBestLength= %d\n\n", dataStruct.bestDistance);
	// printVector(dataStruct.bestWay);

	return 1;
	// return moovingFlag;
}

void restartAnts(AntStruct *ants, Data &dataStuct)
{
	for (size_t i = 0; i < dataStuct.nVerts; i++)
	{
		ants[i].length = 0; 
		ants[i].visited.clear();
		ants[i].unvisited.clear();
		ants[i].visited.push_back(i);//муравей в каждой вершине
		for (size_t n = 0; n <dataStuct.nVerts; n++)
		{
			if (n == i)
				continue;
			ants[i].unvisited.push_back(n);
		}

	}
	
}

void  getNewValues(AntStruct *ants, Data &dataStruct)
{
	double deltaPherom, newPherom, oldPherom;

	for (size_t i = 0; i < dataStruct.nAnts; i++)
	{//для каждого муравья расчитать и разложить феромон по граням пути муравья
		deltaPherom = dataStruct.qVal / ants[i].length;//выделил i-муравей без учета распыления
				printf("\n\nnextAnt:\n");

		for (size_t n = 0; n < dataStruct.nVerts; n++)
		{//для каждой грани пути текущего муравья:
			oldPherom = dataStruct.pheromone[*(ants[i].visited.begin() +n)][*(ants[i].visited.begin() +n +1)];
			newPherom = (dataStruct.rho * deltaPherom) + oldPherom;//распыление феромона
			newPherom = newPherom * (1 - dataStruct.rho);//испарение феромона
			newPherom = (newPherom < 0) ? 0 : newPherom;
			//записываем новый феромон в вектор-феромон:
			dataStruct.pheromone[*(ants[i].visited.begin() +n)][*(ants[i].visited.begin() +n +1)] = newPherom;
							printf("398:oldPherom= %lf\n", oldPherom);
						printf("401newPherom= %lf\n", newPherom);
						printf("distance=%lf\n", ants[i].length);
		}
	}
	
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph)
{
	checkGraph(graph);
	TsmResult ret;
	size_t nVerts = graph.getVerticesNumber();
	// size_t nAnts = nVerts;
	size_t nTimes = 3;//20 * nVerts;
	// double alpha = 1;
	// double beta = 1;
	// double rho = 0.55;
	// double qVal = 100;

	// double pheromone[nVerts];

	AntStruct ants[nVerts];
	// std::vector<std::vector<double>> phero(nVerts);

	//Init:
	Data dataStruct;
	dataStruct.alpha = 1;
	dataStruct.beta = 1;
	dataStruct.rho = 0.55;
	dataStruct.qVal = 100;
	dataStruct.bestDistance = std::numeric_limits<int>::max();
	dataStruct.nAnts = nVerts;
	dataStruct.nVerts = nVerts;
	double initPheromone = 1.0/(double)nVerts;
	dataStruct.pheromone.resize(nVerts);
	for (size_t i = 0; i < nVerts; i++)
	{
		dataStruct.pheromone[i].resize(nVerts);
		for (size_t n = 0; n < nVerts; n++)
		{
			dataStruct.pheromone[i][n] = initPheromone;
		}
	}

	for (size_t i = 0; i < nVerts; i++)
	{
		ants[i].visited.push_back(i);//муравей в каждой вершине
		for (size_t n = 0; n < nVerts; n++)
		{
			if (n == i)
				continue;
			ants[i].unvisited.push_back(n);
		}
		// dataStruct.pheromone[i] = initPheromone;//нач.феромон в каждой вершине
		ants[i].curVert = i;
		ants[i].nextVert = -1;
		// ants[i].antsMax = nAnts;
		ants[i].length = 0;
	}
	//--endInit---

	srand(time(NULL));
	for (size_t i=0; i < nTimes; i++)
	{printf("\n\nNEXT TIME(%d):\n", i);
		// if (antsGoGoGo(ants, graph, dataStruct) == 0)
		// 	getNewValues();
		antsGoGoGo(ants, graph, dataStruct);
		getNewValues(ants, dataStruct);
		// if (i != nTimes)
		restartAnts(ants, dataStruct);
	}
//приравнять два вектора:
// vector1.assign(vector2.begin(), vector2.end());
	// bestWay.assign(ants[1].visited.begin(), ants[1].unvisited.end());
	//return:

	ret.distance=dataStruct.bestDistance;
	ret.vertices.assign(dataStruct.bestWay.begin(), dataStruct.bestWay.end());
	return ret;
}
