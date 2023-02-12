#include "Utilities.hpp"
#include <algorithm>

#ifndef __SORT_HPP__
#define __SORT_HPP__

using namespace Utilities;
/**
 * This should result in a value in its sorted position
 * and to the left smaller items
 * and to the right of it bigger items
 */
template <class RandomAccessIterator>
RandomAccessIterator
partition (RandomAccessIterator first, RandomAccessIterator last)
{

  if (first == last || (first + 1) == last)
    {
      return first;
    }

  RandomAccessIterator pivot = last - 1;

  RandomAccessIterator left = first;
  RandomAccessIterator right = pivot;

  while (left != right)
    {
      while (left != right && *left < *pivot)
        {
          ++left;
        }

      while (left != right && *right > *pivot)
        {
          --right;
        }

      if (left != right)
        {
          std::swap (*left, *right);
        }
    }

  std::swap (*pivot, *left);
  return left;
}

template <class RandomAccessIterator>
void
quickSort (RandomAccessIterator first, RandomAccessIterator last)
{
  RandomAccessIterator p;
  if (first != last)
    {
      p = partition (first, last);
      quickSort (first, p);
      quickSort (++p, last);
    }
}

#endif // __SORT_HPP__