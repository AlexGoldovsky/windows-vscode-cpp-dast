#include "Sort.hpp"
#include "Utilities.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

using namespace Utilities;

/**
 * Quick Sort tests
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
  auto a = new int (4);
  cout << a;

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
 * Merge Sort tests
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
  auto a = new int (4);
  cout << a;

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