#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "kata.kata-iterator.h"
#include "kata.worker.h"
#include "test.main.h"

//                                          1         2         3         4         5         6 
//                                0123456789012345678901234567890123456789012345678901234567890123456789
//                                         6         5         4         3         2         1  
//                                9876543210987654321098765432109876543210987654321098765432109876543210
static std::string kata_sequence("8745648184845171326578518184151512461752149647129746915414816354846454");
//                                               1326        415   245
//                                                                   617


static std::string test_to_string(char *test)
{
  std::string rv("{ ");

  while (*test)
  {
    rv += (*test++) + '0';
  }

  rv += " }";

  return rv;
}


static void check_stack(KataIterator::solution_pair_stack &stack, char *test, int position, int count)
{
  should_eq((int) (stack.top().position - test), position, "position");
  should_eq(stack.top().count, count, "count");
  stack.pop();
}


static void test_find_solution(void)
{
  std::cout << "*** KataWorker::find_solutions(): begin\n";

  {
    KataIterator it(kata_sequence.c_str() + kata_sequence.length() - 1, kata_sequence.c_str());
    KataWorker::find_solutions(&it);
    should_eq(it.stack().size(), 4, kata_sequence);
    /*
    check_stack(it.stack, test.get(), 51, 4);
    check_stack(it.stack, test.get(), 40, 3);
    check_stack(it.stack, test.get(), 34, 3);
    check_stack(it.stack, test.get(), 32, 3);
    */
  }
  
  std::cout << "*** KataWorker::find_solutions(): complete\n";
}


void test_worker(void)
{
  std::cout << "*** KataWorker: begin\n";

  test_find_solution();

  std::cout << "*** KataWorker: complete\n\n";
}
