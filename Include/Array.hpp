#ifndef __SORT_HPP__
#define __SORT_HPP__

#include "Utilities.hpp"

#include <algorithm>
#include <vector>
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

/**
 * Since the algorithms isn't in place, we must have a copy of the data, hence
 * the data type must be provided
 */
template <typename RandomAccessIterator, typename T>
void
mergeSort (const RandomAccessIterator begin, const RandomAccessIterator end)
{

  auto merge =
      [] (const RandomAccessIterator lbegin, const RandomAccessIterator lend,
          const RandomAccessIterator rbegin, const RandomAccessIterator rend) {
        RandomAccessIterator l = lbegin;
        RandomAccessIterator r = rbegin;

        std::vector<T> vi;

        while (l != lend && r != rend)
          {
            if (*l < *r)
              {
                vi.push_back (*l);
                ++l;
              }
            else
              {
                vi.push_back (*r);
                ++r;
              }
          }

        // leftovers
        while (l != lend)
          {
            vi.push_back (*l);
            ++l;
          }

        while (r != rend)
          {
            vi.push_back (*r);
            ++r;
          }

        auto i = vi.begin ();
        auto j = lbegin;

        while (i != vi.end ())
          {
            *j = *i;
            ++i;
            ++j;
          }
      };

  if (begin + 1 == end)
    {
      return;
    }

  auto middle = begin + ((end - begin) / 2);

  mergeSort<RandomAccessIterator, T> (begin, middle);
  mergeSort<RandomAccessIterator, T> (middle, end);

  merge (begin, middle, middle, end);
}

template <class RandomAccessIterator>
void
bubbleSort (RandomAccessIterator first, RandomAccessIterator last)
{
  if (first == last)
    {
      return;
    }

  auto j = last;
  while (j != first)
    {
      auto i = first;
      auto max = first;
      while (i != j)
        {
          if (*max < *i)
            {
              max = i;
            }
          ++i;
        }

      std::swap (*max, *(j - 1));
      --j;
    }
}

template <typename RandomAccessIterator>
RandomAccessIterator
quickSelect (RandomAccessIterator begin, RandomAccessIterator end, size_t k)
{
  if (begin == end)
    {
      return begin;
    }

  auto p = partition (begin, end);

  if ((size_t)(p - begin) > k)
    {
      return quickSelect (begin, p, k);
    }
  else if ((size_t)(p - begin) < k)
    {
      return quickSelect (p, end, k - (size_t)(p - begin));
    }
  else
    {
      return p;
    }
}

#endif // __SORT_HPP__