#include "Graph.hpp"
#include "Utilities.hpp"

#include <gtest/gtest.h>

#include <iostream>

using std::cout;

using namespace Utilities;

TEST (Graph, simple)
{
  Graph<int> g;

  g.addNode (1);
  g.addNode (2);
  g.addEdge (1, 2);
//   print_container (cout, g.begin (), g.end ());
  EXPECT_EQ (1, 1);
}
