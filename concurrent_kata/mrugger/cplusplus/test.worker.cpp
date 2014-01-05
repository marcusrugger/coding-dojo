#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <thread>
#include <cassert>
#include <cstring>
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
  std::cout << "*** KataWorker: test_find_solution: begin\n";

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
  
  std::cout << "*** KataWorker: test_find_solution: complete\n";
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


void test_massive(argument_map *map)
{
  const std::string prefix("*** KataWorker: test_massive: ");
  std::cout << prefix << "begin\n";

  int thread_count    = atoi(map->at(ARGKEY_THREAD_COUNT).c_str());
  int replicant_count = atoi(map->at(ARGKEY_REPLICANT_COUNT).c_str());
  int block_size      = atoi(map->at(ARGKEY_BLOCK_SIZE).c_str());

  int sequence_size = kata_sequence.length();
  int massive_block_size = replicant_count * sequence_size;

  block_size = block_size > 0 ? block_size : massive_block_size;

  printf("thread_count:       %d\n", thread_count);
  printf("replicant_count:    %d\n", replicant_count);
  printf("block_size:         %d\n", block_size);
  printf("sequence_size:      %d\n", sequence_size);
  printf("massive_block_size: %d\n", massive_block_size);

  std::unique_ptr<char> massive_block(new char[massive_block_size]);
  assert(massive_block.get() != NULL);

  for (int a = 0; a < replicant_count; a++)
    memcpy(massive_block.get() + sequence_size * a, kata_sequence.c_str(), sequence_size);

  massive_block.get()[massive_block_size - 1] = '\0';

  /*{
    solution_queue queue;
    std::string sequence(massive_block.get());
    BlockIterator it(sequence, 0, &queue);
    KataWorker::find_all_solutions(&it);
    should_eq(queue.size(), 1, "queue size");
    solution_stack *stack(queue.front().get());
    should_eq(stack->size(), 4 * replicant_count, "stack size");
  }*/

  /*{
    solution_queue queue;
    std::string sequence(massive_block.get());
    BlockIterator it(sequence, 1000000, &queue);
    KataWorker::find_all_solutions(&it);
    should_eq(queue.size(), sequence_size, "queue size");
  }*/

  {
    std::queue<std::unique_ptr<std::thread>> thread_pool;
    solution_queue queue;
    std::string sequence(massive_block.get());
    BlockIterator it(sequence, block_size, &queue);

    for (int a = 0; a < thread_count; a++)
    {
      std::thread *thread(new std::thread(KataWorker::find_all_solutions, &it));
      thread_pool.push(std::unique_ptr<std::thread>(thread));
    }

    while (thread_pool.size() > 0)
    {
      thread_pool.front()->join();
      thread_pool.pop();
    }

    should_eq(queue.size(), (massive_block_size + block_size - 1) / block_size, "queue size");
  }

  std::cout << prefix << "complete\n";
}


void test_worker(argument_map *map)
{
  std::cout << "*** KataWorker: begin\n";

  //test_find_solution();
  //test_with_block_iterator();
  test_massive(map);

  std::cout << "*** KataWorker: complete\n\n";
}
