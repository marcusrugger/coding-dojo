#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "test.main.h"


static std::string bool_to_string(bool flag)
{ return flag ? "true" : "false"; }


void should_eq(bool test_result, bool should_be, std::string description)
{
  if (test_result != should_be)
  {
    std::ostringstream ss;
    ss << description << ": was (" << bool_to_string(test_result) << "), should be (" << bool_to_string(should_be) << ")";
    throw std::runtime_error(ss.str());
  }
  else
  {
    std::cout << "success: " << description << ", result: " << test_result << "\n";
  }
}


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


void should_eq(char *test_result, char *should_be, std::string description)
{
  if (test_result != should_be)
  {
    std::ostringstream ss;
    ss << description << ": was (" << (long int) test_result << "), should be (" << (long int) should_be << ")";
    throw std::runtime_error(ss.str());
  }
  else
  {
    std::cout << "success: " << description << "\n";
  }
}


int main(int argc, char **argv)
{
  test_worker();
}