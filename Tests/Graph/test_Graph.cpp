#include "Graph.hpp"

#include <gtest/gtest.h>
#include <cassert>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

TEST (Graph, simple)
{
  vector<int> v{ 1, -2, 5, 2 };
  vector<int> expected{ -2, 1, 2, 5 };

  EXPECT_EQ (v, expected);
}