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

#include "kata.worker.h"
#include "test.main.h"
#include "kata.unbounded-iterators.h"

//                                         6         5         4         3         2         1  
//                                9876543210987654321098765432109876543210987654321098765432109876543210
//                                          1         2         3         4         5         6 
//                                0123456789012345678901234567890123456789012345678901234567890123456789
static std::string kata_sequence("8745648184845171326578518184151512461752149647129746915414816354846454");
//                                               1326        415   246
//                                                                   617


static void check_stack(match_stack &stack, int expected_position, int expected_count)
{
  should_eq(stack.top().first, expected_position, "position");
  should_eq(stack.top().second, expected_count, "count");
  stack.pop();
}


static std::thread *create_iterator(std::queue<std::unique_ptr<KataUnboundedSequenceIterator>> *queue,
                                    KataUnboundedSequencer *seq, int start, int stop, int match_stop)
{
  match_stack *stack = new match_stack();
  KataUnboundedSequenceIterator *it = new KataUnboundedSequenceIterator(seq, stack, start, stop, match_stop);
  queue->push(std::unique_ptr<KataUnboundedSequenceIterator>(it));
  std::thread *thread(new std::thread(KataWorker::find_solutions, it));
  return thread;
}


static void test_find_solution_with_unbounded(int thread_count, int sequence_size)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  int block_size = sequence_size / thread_count;

  KataUnboundedSequencer sequencer(kata_sequence, sequence_size);
  std::queue<std::unique_ptr<KataUnboundedSequenceIterator>> queue;
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


static void test_find_solution_with_no_overap(int thread_count, int sequence_size)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  KataUnboundedSequencer sequencer(kata_sequence, sequence_size);
  std::queue<std::unique_ptr<KataUnboundedSequenceIterator>> queue;
  std::queue<std::unique_ptr<std::thread>> thread_pool;

  for (int a = 0; a < thread_count; a++)
  {
    int start       = sequence_size - 1;
    int stop        = 0;
    int match_stop  = 0;
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

  test_find_solution_with_no_overap(4, 10000000);

  std::cout << prefix << "complete\n";
}
