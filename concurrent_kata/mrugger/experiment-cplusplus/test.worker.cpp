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
#include "threads.parallelize.h"

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


typedef ThreadsParallelizer<KataUnboundedSequencer, std::function<match_stack *(SequenceIterable *)>, match_stack> Parallelizer;


static void test_find_solution_with_no_overap(int thread_count, int sequence_size)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  KataUnboundedSequencer sequencer(kata_sequence, sequence_size);

  Parallelizer parallelizer(4);
  match_queue *queue;
  queue = (match_queue *) parallelizer.parallelize(&sequencer, KataWorker::find_solutions);

  while (!queue->empty())
  {
    match_stack *stack = queue->front().get();
    printf("map size: %lu\n", stack->size());
    while (!stack->empty())
    {
      match_pair p(stack->top());
      printf("position: %d, count: %d\n", p.first, p.second);
      stack->pop();
    }
    queue->pop();
  }

  if (queue) delete queue;

  std::cout << prefix << "complete\n";
}


void test_worker(argument_map *map)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  test_find_solution_with_no_overap(1, 1);

  std::cout << prefix << "complete\n";
}
