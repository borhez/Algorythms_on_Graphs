#include <gtest/gtest.h>
#include "../navigator/s21_graph/s21_graph_algorithms.h"

class GraphAlgorithmsFixture : public ::testing::Test {

 protected:
  virtual void TearDown() {
	delete _g0;
  }
  void SetUp() override {
	_g0 = new Graph();
	_g1 = new Graph();

  }

  Graph *_g0;
  Graph *_g1;
};

TEST_F(GraphAlgorithmsFixture, depthFirstSearch)
{
  ASSERT_EQ(1, _g0->loadGraphFromFile("unit_test_files/complex2.txt"));
  std::vector<int>arr = GraphAlgorithms::depthFirstSearch(*_g0, 1);
  char exp[]  = {'a', 'd', 'c', 'b', 'e', 96, 96,96, 96 };
  char exp2[]  = {'i', 'f', 96, 96, 96, 96, 96,96, 96 };
  char exp3[]  = {'h', 96, 96, 96, 96, 96, 96,96, 96 };

  for (int i = 0; i < _g0->getVerticesNumber(); ++i)
	EXPECT_EQ(arr[i] + 'a' - 1, exp[i]);

  arr = GraphAlgorithms::depthFirstSearch(*_g0, 9);
  for (int i = 0; i < _g0->getVerticesNumber(); ++i)
	EXPECT_EQ(arr[i] + 'a' - 1, exp2[i]);

  arr = GraphAlgorithms::depthFirstSearch(*_g0, 8);
  for (int i = 0; i < _g0->getVerticesNumber(); ++i)
	EXPECT_EQ(arr[i] + 'a' - 1, exp3[i]);
}

TEST_F(GraphAlgorithmsFixture, getShortestPathBetweenVertices)
{
  ASSERT_EQ(1, _g1->loadGraphFromFile("unit_test_files/deicstra.txt"));
  EXPECT_EQ(60, GraphAlgorithms::getShortestPathBetweenVertices(*_g1, 1, 5));
}