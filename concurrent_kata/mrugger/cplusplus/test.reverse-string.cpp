#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "kata.reverse-string.h"
#include "test.main.h"

//                                          1         2         3         4         5         6 
//                                0123456789012345678901234567890123456789012345678901234567890123456789
//                                         6         5         4         3         2         1  
//                                9876543210987654321098765432109876543210987654321098765432109876543210
static std::string kata_sequence("8745648184845171326578518184151512461752149647129746915414816354846454");
//                                               1326        415   245
//                                                                   617

static std::unique_ptr<char> reverse_string(std::string src)
{
  std::unique_ptr<char> dst(new char[src.length() + 1]);

  const char *src_ptr = src.c_str();
  char *dst_ptr = dst.get() + src.length();
  (*dst_ptr--) = '\0';

  while (*src_ptr)
    (*dst_ptr--) = (*src_ptr++) - '0';

  return dst;
}


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


static void test_match_count(void)
{
  std::cout << "*** KataReverseString::match_count(): begin\n";

  {
    char test[] = { 3, 0 };
    should_eq(KataReverseString::match_count(test), 0, test_to_string(test));
  }

  {
    char test[] = { 3, 2, 0 };
    should_eq(KataReverseString::match_count(test), 0, test_to_string(test));
  }

  {
    char test[] = { 3, 2, 1, 0 };
    should_eq(KataReverseString::match_count(test), 3, test_to_string(test));
  }

  {
    char test[] = { 3, 2, 1, 1, 2, 3, 0 };
    should_eq(KataReverseString::match_count(test), 3, test_to_string(test));
  }

  {
    char test[] = { 5, 1, 1, 1, 1, 1, 2, 3, 4, 0 };
    should_eq(KataReverseString::match_count(test), 6, test_to_string(test));
  }

  {
    char test[] = { 3, 2, 9, 7, 0 };
    should_eq(KataReverseString::match_count(test), 0, test_to_string(test));
  }

  std::cout << "*** KataReverseString::match_count(): complete\n";
}


static void check_stack(KataReverseString::solution_stack &stack, char *test, int position, int count)
{
  should_eq((int) (stack.top().position - test), position, "position");
  should_eq(stack.top().count, count, "count");
  stack.pop();
}


static void test_find_solution(void)
{
  std::cout << "*** KataReverseString::find_solutions(): begin\n";

  {
    char test[] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 4, 0 };
    KataReverseString::solution_stack stack(KataReverseString::find_solutions(test, 12));
    should_eq(stack.size(), 4, test_to_string(test));
    check_stack(stack, test, 9, 2);
    check_stack(stack, test, 8, 3);
    check_stack(stack, test, 7, 3);
    check_stack(stack, test, 4, 2);
  }

  {
    std::unique_ptr<char> test(reverse_string(kata_sequence));
    KataReverseString::solution_stack stack(KataReverseString::find_solutions(test.get(), kata_sequence.length()));
    should_eq(stack.size(), 4, test_to_string(test.get()));
    check_stack(stack, test.get(), 51, 4);
    check_stack(stack, test.get(), 40, 3);
    check_stack(stack, test.get(), 34, 3);
    check_stack(stack, test.get(), 32, 3);
  }
  
  std::cout << "*** KataReverseString::find_solutions(): complete\n";
}


void test_worker(void)
{
  std::cout << "*** KataReverseString: begin\n";

  test_match_count();
  test_find_solution();

  std::cout << "*** KataReverseString: complete\n\n";
}
