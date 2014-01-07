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

#include "kata.sequence-iterator.h"
#include "kata.worker.h"
#include "test.main.h"
#include "test.unbounded-iterators.h"

//                                         6         5         4         3         2         1  
//                                9876543210987654321098765432109876543210987654321098765432109876543210
//                                          1         2         3         4         5         6 
//                                0123456789012345678901234567890123456789012345678901234567890123456789
static std::string kata_sequence("8745648184845171326578518184151512461752149647129746915414816354846454");
//                                               1326        415   246
//                                                                   617


static void check_stack(solution_stack &stack, const char *test, int position, int count)
{
  should_eq((int) (stack.top().position - test), position, "position");
  should_eq(stack.top().count, count, "count");
  stack.pop();
}


static void test_find_solution_one_block(void)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  solution_stack stack;
  SequenceIterator it(kata_sequence.c_str() + kata_sequence.length() - 1, kata_sequence.c_str(), kata_sequence.c_str(), &stack);
  KataWorker::find_solutions(&it);
  should_eq(stack.size(), 4, kata_sequence);
  check_stack(stack, kata_sequence.c_str(), 18, 3);
  check_stack(stack, kata_sequence.c_str(), 29, 2);
  check_stack(stack, kata_sequence.c_str(), 35, 2);
  check_stack(stack, kata_sequence.c_str(), 37, 2);

  std::cout << prefix << "complete\n";
}


static void test_find_solution_two_blocks(void)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  solution_stack stack1;
  solution_stack stack2;

  const char *it1_start (kata_sequence.c_str() + kata_sequence.length() / 2 - 1);
  const char *it1_end   (kata_sequence.c_str());
  const char *it2_start (kata_sequence.c_str() + kata_sequence.length() - 1);
  const char *it2_end   (kata_sequence.c_str() + kata_sequence.length() / 2);

  SequenceIterator it1(it1_start, it1_end, it1_end, &stack1);
  SequenceIterator it2(it2_start, it2_end, it2_end - 8, &stack2);

  KataWorker::find_solutions(&it1);
  KataWorker::find_solutions(&it2);

  should_eq(stack1.size(), 2, "front half of kata sequence");
  should_eq(stack2.size(), 2, "back half of kata sequence");

  check_stack(stack1, kata_sequence.c_str(), 18, 3);
  check_stack(stack1, kata_sequence.c_str(), 29, 2);

  check_stack(stack2, kata_sequence.c_str(), 35, 2);
  check_stack(stack2, kata_sequence.c_str(), 37, 2);

  std::cout << prefix << "complete\n";
}


static std::thread *create_iterator(std::queue<std::unique_ptr<TestUnboundedSequenceIterator>> *queue,
                                    Sequencer *seq, int start, int stop, int match_stop)
{
  match_stack *stack = new match_stack();
  TestUnboundedSequenceIterator *it = new TestUnboundedSequenceIterator(seq, stack, start, stop, match_stop);
  queue->push(std::unique_ptr<TestUnboundedSequenceIterator>(it));
  std::thread *thread(new std::thread(KataWorker::find_solutions, it));
  return thread;
}


static void test_find_solution_with_unbounded(int thread_count, int sequence_size)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  int block_size = sequence_size / thread_count;

  TestUnboundedSequencer sequencer(kata_sequence, sequence_size);
  std::queue<std::unique_ptr<TestUnboundedSequenceIterator>> queue;
  std::queue<std::unique_ptr<std::thread>> thread_pool;

  thread_pool.push(std::unique_ptr<std::thread>(create_iterator(&queue, &sequencer, block_size-1, 0, 0)));

  for (int a = 1; a < thread_count; a++)
  {
    int start       = (a+1) * block_size - 1;
    int stop        = a * block_size;
    int match_stop  = stop - 8;
    thread_pool.push(std::unique_ptr<std::thread>(create_iterator(&queue, &sequencer, start, stop, match_stop)));
  }

  while (thread_pool.size() > 0)
  {
    thread_pool.front()->join();
    thread_pool.pop();
  }

  while (queue.size() > 0)
  {
    printf("stack size: %lu\n", queue.front()->_stack->size());
    queue.pop();
  }

  std::cout << prefix << "complete\n";
}


void test_worker(argument_map *map)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  //test_find_solution_one_block();
  //test_find_solution_two_blocks();
  test_find_solution_with_unbounded(4, 70 * 1000000 * 5);

  std::cout << prefix << "complete\n";
}
