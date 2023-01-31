#include <gtest/gtest.h>
#include "../navigator/s21_graph/s21_graph.h"

class GraphFixture : public ::testing::Test {

 protected:
  virtual void TearDown() {
	delete _g0;
	delete _g1;
	delete _g2;
  }
  void SetUp() override {
	_g0 = new Graph();
	_g1 = new Graph();
	_g2 = new Graph();

	_g1->loadGraphFromFile("unit_test_files/complex.txt");
  }

  Graph *_g0;
  Graph *_g1;
  Graph *_g2;
};

// !!! Как тестить деструктор?
TEST_F(GraphFixture, GraphConstructorIsEmpty) {
  EXPECT_EQ(0, _g0->getVerticesNumber());
}

TEST_F(GraphFixture, loadGraphFromFile)
{
  EXPECT_EQ(1, _g0->loadGraphFromFile("unit_test_files/complex.txt"));

  EXPECT_EQ(-1, _g0->loadGraphFromFile("unit_test_files/wrongPath.txt"));
  EXPECT_EQ(-1, _g0->loadGraphFromFile("unit_test_files/complex_wrong_cols.txt"));
  EXPECT_EQ(-1, _g0->loadGraphFromFile("unit_test_files/complex_wrong_rows.txt"));
  EXPECT_EQ(-1, _g0->loadGraphFromFile("unit_test_files/complex_wrongNum.txt"));
  EXPECT_EQ(-1, _g0->loadGraphFromFile("unit_test_files/complex_wrongFormat.txt"));
}

void compareFiles(std::string const &file, std::string const &expected_file)
{
  std::ifstream fin;
  fin.open(file, std::ios::in);
  if(!fin.is_open() || fin.bad())
	throw std::invalid_argument("cant open file");
  std::ifstream ex_fin;
  ex_fin.open(expected_file, std::ios::in);
  if(!ex_fin.is_open() || ex_fin.bad())
	throw std::invalid_argument("cant open expected");

  std::string s, eS;
  while (std::getline(fin, s) && std::getline(ex_fin, eS))
	EXPECT_EQ(s, eS);
  EXPECT_EQ(fin.eof(), ex_fin.eof());
  ex_fin.close();
  fin.close();
}

TEST_F(GraphFixture, exportGraphToDot)
{
  _g2->loadGraphFromFile("unit_test_files/digraph.txt");
  _g2->exportGraphToDot("unit_test_files/digraph.dot");
  compareFiles("unit_test_files/digraph.dot", "unit_test_files/digraph_expected.dot");

  _g2->loadGraphFromFile("unit_test_files/graph.txt");
  _g2->exportGraphToDot("unit_test_files/graph.dot");
  compareFiles("unit_test_files/graph.dot", "unit_test_files/graph_expected.dot");
}

TEST_F(GraphFixture, getDistCheck) {
  //empty
  EXPECT_THROW(_g0->getDist(0,0), std::out_of_range);
  //loop
  EXPECT_EQ(1, _g1->getDist(7,7));
  //ordinary
  EXPECT_EQ(1, _g1->getDist(6,8));
  EXPECT_EQ(0, _g1->getDist(3,3));
}
TEST_F(GraphFixture, getVerticesNumberCheck)
{
  //empty
  EXPECT_EQ(0, _g0->getVerticesNumber());
  //for_unit_test.txt
  EXPECT_EQ(9, _g1->getVerticesNumber());
}