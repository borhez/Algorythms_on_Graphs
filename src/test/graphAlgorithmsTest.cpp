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
  EXPECT_EQ(30, GraphAlgorithms::getShortestPathBetweenVertices(*_g1, 4, 5));

  EXPECT_EQ(std::numeric_limits<double>::infinity(),
			GraphAlgorithms::getShortestPathBetweenVertices(*_g1, 1, 6));

  EXPECT_EQ(0,
			GraphAlgorithms::getShortestPathBetweenVertices(*_g1, 1, 1));
}

TEST_F(GraphAlgorithmsFixture, TSM_test_nVerts_from_result_struct)
{
  ASSERT_EQ(1, _g0->loadGraphFromFile("unit_test_files/saleman21.txt"));
  // ASSERT_EQ(1, _g0->loadGraphFromFile("/home/sshield/projects/sber/navigator/curGit/src/cmake-build-debug/unit_test_files/saleman21.txt"));  
  size_t nVert=_g0->getVerticesNumber() + 1;
  TsmResult res = GraphAlgorithms::solveTravelingSalesmanProblem(*_g0);
  EXPECT_EQ(nVert, res.vertices.size());
}

TEST_F(GraphAlgorithmsFixture, TSM_test_result_distance_gt_zero)
{
  ASSERT_EQ(1, _g0->loadGraphFromFile("unit_test_files/saleman21.txt"));
  // ASSERT_EQ(1, _g0->loadGraphFromFile("/home/sshield/projects/sber/navigator/curGit/src/cmake-build-debug/unit_test_files/saleman21.txt"));
  TsmResult res = GraphAlgorithms::solveTravelingSalesmanProblem(*_g0);
  EXPECT_GT(res.distance,  0);
}

TEST_F(GraphAlgorithmsFixture, TSM_test_errorFlag)
{
  ASSERT_EQ(1, _g0->loadGraphFromFile("unit_test_files/salemanError1.txt"));
  // ASSERT_EQ(1, _g0->loadGraphFromFile("/home/sshield/projects/sber/navigator/curGit/src/cmake-build-debug/unit_test_files/salemanError1.txt"));

  std::ofstream out("out.txt");
  std::streambuf *coutbuf= std::cout.rdbuf();//save old buf
  std::cout.rdbuf(out.rdbuf());//redirect std::cout to out.txt!

  TsmResult res = GraphAlgorithms::solveTravelingSalesmanProblem(*_g0);
  std::string test;
  std::ifstream f("out.txt");
  std::stringstream ss;
  ss << f.rdbuf();
  test = ss.str();
  std::cout.rdbuf(coutbuf); //reset to standard output again

  EXPECT_EQ(test, "Error Graph\n");
}

TEST_F(GraphAlgorithmsFixture, MinOstovTree_check_resultMatrix)
{
  ASSERT_EQ(1, _g0->loadGraphFromFile("unit_test_files/prima7.txt"));
  // ASSERT_EQ(1, _g0->loadGraphFromFile("/home/sshield/projects/sber/navigator/curGit/src/cmake-build-debug/unit_test_files/prima7.txt"));

  std::vector<std::vector<int>> test;
  test.resize(_g0->getVerticesNumber());
  test[0]={0, 0, 0, 0, 5, 1, 0};
  test[1]={0, 0, 0, 0, 0, 0, 0};
  test[2]={0, 3, 0, 0, 0, 0, 0};
  test[3]={0, 0, 0, 0, 0, 0, 0};
  test[4]={0, 0, 0, 0, 0, 0, 1};
  test[5]={0, 0, 1, 1, 0, 0, 0};
  test[6]={0, 0, 0, 0, 0, 0, 0};

  EXPECT_EQ(test, GraphAlgorithms::getLeastSpanningTree(*_g0));
  
  //-----------------------------------------------------------
  ASSERT_EQ(1, _g0->loadGraphFromFile("unit_test_files/prima5.txt"));
  // ASSERT_EQ(1, _g0->loadGraphFromFile("/home/sshield/projects/sber/navigator/curGit/src/cmake-build-debug/unit_test_files/prima5.txt"));
  
  std::vector<std::vector<int>> test2;
  test2.resize(_g0->getVerticesNumber());
  test2[0]={0, 0, 0, 2, 5};
  test2[1]={0, 0, 0, 0, 0};
  test2[2]={0, 3, 0, 0, 0};
  test2[3]={0, 0, 1, 0, 0};
  test2[4]={0, 0, 0, 0, 0};

  EXPECT_EQ(test2, GraphAlgorithms::getLeastSpanningTree(*_g0));

  //-----------------------------------------------------------
  ASSERT_EQ(1, _g0->loadGraphFromFile("unit_test_files/prima4.txt"));
  // ASSERT_EQ(1, _g0->loadGraphFromFile("/home/sshield/projects/sber/navigator/curGit/src/cmake-build-debug/unit_test_files/prima4.txt"));
  
  std::vector<std::vector<int>> test3;
  test3.resize(_g0->getVerticesNumber());
  test3[0]={0, 0, 0, 2};
  test3[1]={0, 0, 0, 0};
  test3[2]={0, 0, 0, 0};
  test3[3]={0, 3, 7, 0};

  EXPECT_EQ(test3, GraphAlgorithms::getLeastSpanningTree(*_g0));
}