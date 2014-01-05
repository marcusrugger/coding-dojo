#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <thread>

#include "kata.kata-iterator.h"
#include "kata.block-iterator.h"
#include "kata.worker.h"
#include "test.main.h"

//                                         6         5         4         3         2         1  
//                                9876543210987654321098765432109876543210987654321098765432109876543210
//                                          1         2         3         4         5         6 
//                                0123456789012345678901234567890123456789012345678901234567890123456789
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


static void check_stack(solution_stack &stack, const char *test, int position, int count)
{
  should_eq((int) (stack.top().position - test), position, "position");
  should_eq(stack.top().count, count, "count");
  stack.pop();
}


static void test_find_solution(void)
{
  std::cout << "*** KataWorker::find_solutions(): begin\n";

  {
    solution_stack stack;
    KataIterator it(kata_sequence.c_str() + kata_sequence.length() - 1, kata_sequence.c_str(), kata_sequence.c_str(), &stack);
    KataWorker::find_solutions(&it);
    should_eq(stack.size(), 4, kata_sequence);
    check_stack(stack, kata_sequence.c_str(), 18, 3);
    check_stack(stack, kata_sequence.c_str(), 29, 2);
    check_stack(stack, kata_sequence.c_str(), 35, 2);
    check_stack(stack, kata_sequence.c_str(), 37, 2);
  }

  {
    solution_stack stack1;
    solution_stack stack2;

    const char *it1_start (kata_sequence.c_str() + kata_sequence.length() / 2 - 1);
    const char *it1_end   (kata_sequence.c_str());
    const char *it2_start (kata_sequence.c_str() + kata_sequence.length() - 1);
    const char *it2_end   (kata_sequence.c_str() + kata_sequence.length() / 2);

    KataIterator it1(it1_start, it1_end, it1_end, &stack1);
    KataIterator it2(it2_start, it2_end, it2_end - 8, &stack2);

    KataWorker::find_solutions(&it1);
    KataWorker::find_solutions(&it2);

    should_eq(stack1.size(), 2, "front half of kata sequence");
    should_eq(stack2.size(), 2, "back half of kata sequence");

    check_stack(stack1, kata_sequence.c_str(), 18, 3);
    check_stack(stack1, kata_sequence.c_str(), 29, 2);

    check_stack(stack2, kata_sequence.c_str(), 35, 2);
    check_stack(stack2, kata_sequence.c_str(), 37, 2);
  }
  
  std::cout << "*** KataWorker::find_solutions(): complete\n";
}


static void test_with_block_iterator(void)
{
  {
    solution_queue queue;
    BlockIterator it(kata_sequence, 0, &queue);
    KataWorker::find_all_solutions(&it);
    should_eq(queue.size(), 1, "queue size");
    solution_stack *stack(queue.front().get());
    should_eq(stack->size(), 4, "stack size");
  }

  {
    solution_queue queue;
    BlockIterator it(kata_sequence, 20, &queue);

    KataWorker::find_all_solutions(&it);
    should_eq(queue.size(), 4, "queue size");

    solution_stack *stack(queue.front().get());
    should_eq(stack->size(), 1, "stack size");
    check_stack(*stack, kata_sequence.c_str(), 18, 3);

    queue.pop();
    stack = queue.front().get();
    should_eq(stack->size(), 3, "stack size");
    check_stack(*stack, kata_sequence.c_str(), 29, 2);
    check_stack(*stack, kata_sequence.c_str(), 35, 2);
    check_stack(*stack, kata_sequence.c_str(), 37, 2);

    queue.pop();
    stack = queue.front().get();
    should_eq(stack->size(), 0, "stack size");

    queue.pop();
    stack = queue.front().get();
    should_eq(stack->size(), 0, "stack size");
  }
}


void test_worker(void)
{
  std::cout << "*** KataWorker: begin\n";

  test_find_solution();
  test_with_block_iterator();

  std::cout << "*** KataWorker: complete\n\n";
}
