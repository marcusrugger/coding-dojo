#include "kata.worker.h"


int KataWorker::match_count(char *numbers)
{
  int sum(0);
  char *ptr(numbers);
  char value(*ptr++);
  while (*ptr && sum < value)
    sum += *ptr++;

  return (sum == value) ? ptr - numbers : 0;
}
