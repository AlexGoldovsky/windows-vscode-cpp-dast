#include "Header\Sort.hpp"
#include "Header\Utilities.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>



#define DEFAULT_TEST_CASE "all"
#define DEFAULT_COMMAND "test"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace Utilities;

int
main (int argc, char *argv[])
{
    

  string command = DEFAULT_COMMAND;
  string test_case = DEFAULT_TEST_CASE;
  if (argc > 1)
    {
        test_case = argv[1];
    }
}