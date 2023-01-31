#include <gtest/gtest.h>
#include "../navigator/s21_graph/s21_graph_algorithms.h"

class GraphAlgorithmsFixture : public ::testing::Test {

 protected:
  virtual void TearDown() {
	delete _g0;
  }
  void SetUp() override {
	_g0 = new Graph();

	ASSERT_EQ(1, _g0->loadGraphFromFile("unit_test_files/complex.txt"));
  }

  Graph *_g0;
};

TEST_F(GraphAlgorithmsFixture, depthFirstSearch)
{
  int *arr = GraphAlgorithms::depthFirstSearch(*_g0, 1);
  int exp[]  = {1, 4, 3, 2, 5, 6, 7, 9, 8 };

  for (int i = 0; i < _g0->getVerticesNumber(); ++i)
	EXPECT_EQ(arr[i], exp[i]);
  delete[] arr;
}