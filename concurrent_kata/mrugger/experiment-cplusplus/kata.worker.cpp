#include <cassert>
#include "kata.worker.h"


match_stack *KataWorker::find_matches(SequenceIterable *sequence_it)
{
  return sequence_it->for_each(match_count);
}


int KataWorker::match_count(CharIterable *it)
{
  assert(it != NULL);

  int count   = 0;
  char value  = it->next();

  char c;
  while ((value > 0) && (c = it->next()))
  {
    value -= c;
    count++;
  }

  return (value == 0) ? count : 0;
}
