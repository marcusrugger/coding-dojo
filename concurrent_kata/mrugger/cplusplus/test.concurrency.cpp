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
#include "kata.block-iterator.h"
#include "kata.worker.h"
#include "test.main.h"

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


class TestConcurrency
{
private:

  int _thread_count;
  int _replicant_count;
  int _block_size;

  int _sequence_size;
  int _massive_block_size;

  std::unique_ptr<char> _massive_block;


public:

  TestConcurrency(int thread_count, int replicant_count, int block_size)
  : _thread_count(thread_count), _replicant_count(replicant_count)
  {
    _sequence_size = kata_sequence.length();
    _massive_block_size = _replicant_count * _sequence_size;

    _block_size = block_size > 0 ? block_size : _massive_block_size;

    _massive_block.reset(new char[_massive_block_size]);
    replicate_sequence(_massive_block.get(), kata_sequence, replicant_count);
  }


  void run(void)
  {
    const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
    std::cout << prefix << "begin\n";
    print_parameters();

    solution_queue queue;
    std::string sequence(_massive_block.get());
    BlockIterator it(sequence, _block_size, &queue);

    run_the_test(&it);
    evaluate_the_test(queue);

    std::cout << prefix << "complete\n";
  }


private:

  void replicate_sequence(char *dst, std::string &sequence, int replicant_count)
  {
    int sequence_size = sequence.length();

    for (int a = 0; a < replicant_count; a++)
      memcpy(dst + sequence_size * a, sequence.c_str(), sequence_size);
  }


  void print_parameters(void)
  {
    printf("thread_count:       %d\n", _thread_count);
    printf("replicant_count:    %d\n", _replicant_count);
    printf("block_size:         %d\n", _block_size);
    printf("sequence_size:      %d\n", _sequence_size);
    printf("massive_block_size: %d\n", _massive_block_size);
  }


  void run_the_test(BlockIterator *it)
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
    should_eq(queue.size(), (_massive_block_size + _block_size - 1) / _block_size, "queue size");

    int count = 0;
    while (queue.size() > 0)
    {
      count += queue.front()->size();
      queue.pop();
    }

    should_eq(count, 4 * _replicant_count, "total matches");
  }

};


void test_concurrency(argument_map *map)
{
  const std::string prefix(std::string("*** ") + __FILE__ + ": " + __FUNCTION__ + ": ");
  std::cout << prefix << "begin\n";

  std::unique_ptr<TestConcurrency> test;

  test.reset(new TestConcurrency(1, 1, 0));
  test->run();

  test.reset(new TestConcurrency(2, 1, 0));
  test->run();

  test.reset(new TestConcurrency(1, 1, 1));
  test->run();

  test.reset(new TestConcurrency(10, 1000, 1));
  test->run();

  test.reset(new TestConcurrency(4, 1000000, 1000));
  test->run();

  std::cout << prefix << "complete\n";
}
