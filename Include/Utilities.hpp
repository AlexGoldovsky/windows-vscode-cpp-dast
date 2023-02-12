#include <iostream>

#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

namespace Utilities
{

template <typename IteratorType>
void
print_container (std::ostream &out, IteratorType first, IteratorType last)
{
  IteratorType it (first);
  while (it != last)
    {
      out << *(it++) << " ";
    }
  out << std::endl;
}

} // namespace utilities

#endif // __UTILITIES_HPP__