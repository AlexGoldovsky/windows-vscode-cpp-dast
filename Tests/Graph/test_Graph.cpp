#include "Graph.hpp"
#include "Utilities.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

using namespace Utilities;

template <typename T> class Functor
{
private:
  std::vector<T> &v_;

public:
  void
  operator() (const T &elem)
  {
    v_.push_back (elem);
  }

  Functor (std::vector<T> &v) : v_ (v){};

  ~Functor (){};
};

TEST (Graph, simple)
{
  vector<int> v (2);
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);
  g.addEdge (1, 2);
  g.addEdge (2, 1);

  std::copy (DfsIterator<Container<int>, int> (g.begin ()),
             DfsIterator<Container<int>, int> (g.end ()), v.begin ());

  vector<int> expected{ 2, 1 };
  EXPECT_EQ (v, expected);
}

TEST (Graph, DfsFromRoot)
{
  vector<int> v;
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);
  g.addEdge (1, 2);

  g.DFS (1, Functor<int> (v));

  vector<int> expected{ 1, 2 };
  EXPECT_EQ (v, expected);
}

TEST (Graph, DfsFromLeaf)
{
  vector<int> v;
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);
  g.addEdge (1, 2);

  g.DFS (2, Functor<int> (v));

  vector<int> expected{ 2 };
  EXPECT_EQ (v, expected);
}

TEST (Graph, CC_2_nodes_no_edge)
{
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);

  auto num_componenets = g.CC ();
  EXPECT_EQ (num_componenets, 2);
}

TEST (Graph, CC_2_nodes_with_edge)
{
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);
  g.addEdge (1, 2);
  g.addEdge (2, 1);

  auto num_componenets = g.CC ();
  EXPECT_EQ (num_componenets, 1);
}

TEST (Graph, CC_5_nodes_fully_connected)
{
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);
  g.addNode (3);
  g.addNode (4);
  g.addNode (5);

  // connect 1
  g.addEdge (1, 2);
  g.addEdge (2, 1);

  g.addEdge (1, 3);
  g.addEdge (3, 1);

  g.addEdge (1, 4);
  g.addEdge (4, 1);

  g.addEdge (1, 5);
  g.addEdge (5, 1);

  // connect 2
  g.addEdge (2, 3);
  g.addEdge (3, 2);

  g.addEdge (2, 4);
  g.addEdge (4, 2);

  g.addEdge (2, 5);
  g.addEdge (5, 2);

  // connect 3
  g.addEdge (3, 4);
  g.addEdge (4, 3);
  
  // connect 4
  g.addEdge (4, 5);
  g.addEdge (5, 4);

  auto num_componenets = g.CC ();
  EXPECT_EQ (num_componenets, 1);
}

TEST (Graph, CC_5_nodes_partially_connected)
{
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);
  g.addNode (3);
  g.addNode (4);
  g.addNode (5);

  g.addEdge (1, 2);
  g.addEdge (2, 1);

  g.addEdge (3, 4);
  g.addEdge (4, 3);
  
  auto num_componenets = g.CC ();
  EXPECT_EQ (num_componenets, 3);
}