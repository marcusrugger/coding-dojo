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
#include "kata.stream-iterator.h"
#include "kata.worker.h"
#include "test.main.h"
#include "test.stream.h"

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


class TestWithStream
{
private:

  int _thread_count;
  int _replicant_count;
  unsigned int _block_size;


public:

  TestWithStream(int thread_count, int replicant_count, unsigned int block_size)
  : _thread_count(thread_count), _replicant_count(replicant_count)
  {
    _block_size = block_size > 0 ? block_size : kata_sequence.length() * replicant_count;
  }


  void run(void)
  {
    const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
    std::cout << prefix << "begin\n";
    print_parameters();

    solution_queue queue;
    TestStream *stream = new TestStream(kata_sequence, _replicant_count);
    StreamIterator it(std::unique_ptr<TestStream>(stream), _block_size, &queue);

    run_the_test(&it);
    evaluate_the_test(queue);

    std::cout << prefix << "complete\n";
  }


private:


  void print_parameters(void)
  {
    printf("thread_count:       %d\n", _thread_count);
    printf("replicant_count:    %d\n", _replicant_count);
    printf("block_size:         %d\n", _block_size);
  }


  void run_the_test(StreamIterator *it)
  {
    std::queue<std::unique_ptr<std::thread>> thread_pool;

    for (int a = 0; a < _thread_count; a++)
    {
      std::thread *thread(new std::thread(KataWorker::find_all_solutions, it));
      thread_pool.push(std::unique_ptr<std::thread>(thread));
    }

    while (thread_pool.size() > 0)
    {
      thread_pool.front()->join();
      thread_pool.pop();
    }
  }


  void evaluate_the_test(solution_queue &queue)
  {
    //should_eq(queue.size(), (_massive_block_size + _block_size - 1) / _block_size, "queue size");

    int count = 0;
    while (queue.size() > 0)
    {
      count += queue.front()->size();
      queue.pop();
    }

    should_eq(count, 4 * _replicant_count, "total matches");
  }

};


void test_with_stream(argument_map *map)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  std::unique_ptr<TestWithStream> test;

  /* TestWithStream(thread_count, replicant_count, block_size) */

  test.reset(new TestWithStream(1, 1, 0));
  test->run();

  test.reset(new TestWithStream(2, 1, 0));
  test->run();

  test.reset(new TestWithStream(4, 1000000, 1000));
  test->run();

  std::cout << prefix << "complete\n";
}
