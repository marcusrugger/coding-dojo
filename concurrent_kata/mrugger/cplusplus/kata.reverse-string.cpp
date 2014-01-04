#include <cassert>
#include "kata.reverse-string.h"


KataReverseString::solution_stack KataReverseString::find_solutions(char *numbers, int count)
{
  assert(numbers != NULL);

  solution_stack stack;
  for (int a = 0; a < count; a++, numbers++)
  {
    int match_result(match_count(numbers));
    if (match_result > 0)
      stack.push(solution_pair(numbers, match_result));
  }

  return stack;
}


int KataReverseString::match_count(char *numbers)
{
  assert(numbers != NULL);

  int sum(0);
  char *ptr(numbers);
  char value(*ptr++);
  while (*ptr && sum < value)
    sum += *ptr++;

  return (sum == value) ? ptr - numbers : 0;
}
