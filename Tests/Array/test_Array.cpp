#include "Array.hpp"
#include "Utilities.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

using namespace Utilities;

/**
 * quickSort tests
 */
TEST (quickSort, simple)
{
  vector<int> v{ 1, -2, 5, 2 };
  quickSort (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2, 5 };

  EXPECT_EQ (v, expected);
}

TEST (quickSort, sorted)
{
  vector<int> v{ -2, 1, 2, 5 };
  quickSort (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2, 5 };

  EXPECT_EQ (v, expected);
}

TEST (quickSort, single_element)
{
  vector<int> v{ -2 };
  quickSort (v.begin (), v.end ());

  vector<int> expected{ -2 };

  EXPECT_EQ (v, expected);
}

TEST (quickSort, odd_number_elements)
{
  vector<int> v{ 1, -2, 2 };
  quickSort (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2 };

  EXPECT_EQ (v, expected);
}

TEST (quickSort, complete_reverse)
{
  vector<int> v{ 2, 1, -2 };
  quickSort (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2 };

  EXPECT_EQ (v, expected);
}

/**
 * mergeSort tests
 */
TEST (mergeSort, simple)
{
  vector<int> v{ 1, -2, 5, 2 };
  mergeSort<vector<int>::iterator, int> (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2, 5 };

  EXPECT_EQ (v, expected);
}

TEST (mergeSort, sorted)
{
  vector<int> v{ -2, 1, 2, 5 };
  mergeSort<vector<int>::iterator, int> (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2, 5 };

  EXPECT_EQ (v, expected);
}

TEST (mergeSort, single_element)
{
  vector<int> v{ -2 };
  mergeSort<vector<int>::iterator, int> (v.begin (), v.end ());

  vector<int> expected{ -2 };

  EXPECT_EQ (v, expected);
}

TEST (mergeSort, odd_number_elements)
{
  vector<int> v{ 1, -2, 2 };
  mergeSort<vector<int>::iterator, int> (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2 };

  EXPECT_EQ (v, expected);
}

TEST (mergeSort, complete_reverse)
{
  vector<int> v{ 2, 1, -2 };
  mergeSort<vector<int>::iterator, int> (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2 };

  EXPECT_EQ (v, expected);
}

/**
 * bubbleSort tests
 */
TEST (bubbleSort, simple)
{
  vector<int> v{ 1, -2, 5, 2 };
  bubbleSort (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2, 5 };

  EXPECT_EQ (v, expected);
}

TEST (bubbleSort, sorted)
{
  vector<int> v{ -2, 1, 2, 5 };
  bubbleSort (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2, 5 };

  EXPECT_EQ (v, expected);
}

TEST (bubbleSort, single_element)
{
  vector<int> v{ -2 };
  bubbleSort (v.begin (), v.end ());

  vector<int> expected{ -2 };

  EXPECT_EQ (v, expected);
}

TEST (bubbleSort, odd_number_elements)
{
  vector<int> v{ 1, -2, 2 };
  bubbleSort (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2 };

  EXPECT_EQ (v, expected);
}

TEST (bubbleSort, complete_reverse)
{
  vector<int> v{ 2, 1, -2 };
  bubbleSort (v.begin (), v.end ());

  vector<int> expected{ -2, 1, 2 };

  EXPECT_EQ (v, expected);
}

/**
 * quickSelect Tests
*/
TEST (quickSelect, simple0)
{
  vector<int> v{ 1, -2, 5, 2 };
  auto i = quickSelect (v.begin (), v.end (), 0);

  int expected = -2;

  EXPECT_EQ (*i, expected);
}

TEST (quickSelect, simple1)
{
  vector<int> v{ 1, -2, 5, 2 };
  auto i = quickSelect (v.begin (), v.end (), 1);

  int expected = 1;

  EXPECT_EQ (*i, expected);
}

TEST (quickSelect, simple2)
{
  vector<int> v{ 1, -2, 5, 2 };
  auto i = quickSelect (v.begin (), v.end (), 2);

  int expected = 2;

  EXPECT_EQ (*i, expected);
}

TEST (quickSelect, simple3)
{
  vector<int> v{ 1, -2, 5, 2 };
  auto i = quickSelect (v.begin (), v.end (), 3);

  int expected = 5;

  EXPECT_EQ (*i, expected);
}

TEST (quickSelect, single_element)
{
  vector<int> v{ 1};
  auto i = quickSelect (v.begin (), v.end (), 0);

  int expected = 1;

  EXPECT_EQ (*i, expected);
}