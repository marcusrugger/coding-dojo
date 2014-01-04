#include <cassert>
#include "kata.worker.h"


void KataWorker::find_solutions(KataIterable *it)
{
  assert(it != NULL);
  
  while (!it->is_done())
  {
    std::unique_ptr<CharIterable> charit(it->current());
    it->push_match_count(match_count(charit.get()));
    it->next();
  }
}


int KataWorker::match_count(CharIterable *it)
{
  assert(it != NULL);

  int sum(0);
  int count(0);

  char value(it->current());
  it->next();

  while (!it->is_done() && sum < value)
  {
    sum += it->current();
    it->next();
    count++;
  }

  return (sum == value) ? count : 0;
}
