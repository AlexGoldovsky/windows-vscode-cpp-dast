#include "Graph.hpp"
#include "Utilities.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

using namespace Utilities;

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
