#include <cassert>
#include "kata.worker.h"


void KataWorker::find_solutions(SequenceIterable *sequence_it)
{
  sequence_it->for_each(match_count);
}


int KataWorker::match_count(CharIterable *it)
{
  assert(it != NULL);

  int sum     = 0;
  int count   = 0;
  char value  = it->next();

  char c = it->next();
  while (c != '\0' && sum < value)
  {
    sum += c;
    count++;
    c = it->next();
  }

  return (sum == value) ? count : 0;
}
