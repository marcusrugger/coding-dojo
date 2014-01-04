#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "kata.worker.h"


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
    std::cout << "success: " << description << "\n";
  }
}


int main(int argc, char **argv)
{
  KataWorker worker;
  char test1[] = { 3, 0 };
  char test2[] = { 3, 2, 0 };
  char test3[] = { 3, 2, 1, 0 };
  char test4[] = { 3, 2, 1, 1, 2, 3, 0 };
  char test5[] = { 5, 1, 1, 1, 1, 1, 0 };
  char test6[] = { 3, 2, 9, 7, 0 };

  should_eq(worker.match_count(test1), 0, "3");
  should_eq(worker.match_count(test2), 0, "32");
  should_eq(worker.match_count(test3), 3, "321");
  should_eq(worker.match_count(test4), 3, "321123");
  should_eq(worker.match_count(test5), 6, "511111");
  should_eq(worker.match_count(test6), 0, "3297");
}
