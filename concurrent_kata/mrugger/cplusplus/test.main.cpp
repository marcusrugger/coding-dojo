#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "test.main.h"


void should_eq(int test_result, int should_be, std::string description)
{
  if (test_result != should_be)
  {
    std::ostringstream ss;
    ss << description << ": was (" << test_result << "), should be (" << should_be << ")";
    throw std::runtime_error(ss.str());
  }
  else
  {
    std::cout << "success: " << description << ", result: " << test_result << "\n";
  }
}


int main(int argc, char **argv)
{
  test_worker();
}