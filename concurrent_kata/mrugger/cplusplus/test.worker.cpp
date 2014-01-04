#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "kata.worker.h"
#include "test.main.h"


static void test_match_count(void)
{
  std::cout << "*** KataWorker.match_count(): begin\n";

  KataWorker worker;
  char test1[] = { 3, 0 };
  char test2[] = { 3, 2, 0 };
  char test3[] = { 3, 2, 1, 0 };
  char test4[] = { 3, 2, 1, 1, 2, 3, 0 };
  char test5[] = { 5, 1, 1, 1, 1, 1, 2, 3, 4, 0 };
  char test6[] = { 3, 2, 9, 7, 0 };

  should_eq(worker.match_count(test1), 0, "3");
  should_eq(worker.match_count(test2), 0, "32");
  should_eq(worker.match_count(test3), 3, "321");
  should_eq(worker.match_count(test4), 3, "321123");
  should_eq(worker.match_count(test5), 6, "511111234");
  should_eq(worker.match_count(test6), 0, "3297");

  std::cout << "*** KataWorker.match_count(): complete\n";
}


void test_worker(void)
{
  std::cout << "*** KataWorker: begin\n";

  test_match_count();

  std::cout << "*** KataWorker: complete\n\n";
}
