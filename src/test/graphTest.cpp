#include <gtest/gtest.h>
#include "../navigator/s21_graph/s21_graph.h"

class GraphFixture : public ::testing::Test {

 protected:
  virtual void TearDown() {
	delete _g0;
  }
  void SetUp() override {
	_g0 = new Graph();
  }

  Graph *_g0;
};

TEST_F(GraphFixture, GraphConstructorIsEmpty) {
  EXPECT_EQ(0, _g0->getVerticesNumber());
}

TEST_F(GraphFixture, getDistCheck) {
  EXPECT_THROW(_g0->getDist(0,0), std::out_of_range);
}
