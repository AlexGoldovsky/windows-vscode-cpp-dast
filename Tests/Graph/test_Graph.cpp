#include "Graph.hpp"
#include "Utilities.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;

using namespace Utilities;

TEST (Graph, simple)
{
  vector<int> v(2);
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);
  g.addEdge (1, 2);

  std::copy(g.begin(), g.end(), v.begin());
//   std::copy(DfsIterator<Container<int>, int>(g.begin()), DfsIterator<Container<int>, int>(g.end()), v.begin());
//   print_container (cout, g.begin (), g.end ());
  EXPECT_EQ (1, 1);
}
