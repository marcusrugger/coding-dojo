#include <cassert>
#include "kata.worker.h"


void KataWorker::find_all_solutions(BlockIterator *it)
{
  assert(it != NULL);

  std::unique_ptr<KataIterator> kata_it(it->next());
  while (kata_it.get() != NULL)
  {
    find_solutions(kata_it.get());
    kata_it.reset(it->next().release());
  }
}


void KataWorker::find_solutions(KataIterator *it)
{
  assert(it != NULL);
  
  std::unique_ptr<CharDecrementIterator> char_it(it->next());
  while (char_it.get() != NULL)
  {
    it->push_match_count(match_count(char_it.get()));
    char_it.reset(it->next().release());
  }
}


int KataWorker::match_count(CharDecrementIterator *it)
{
  assert(it != NULL);

  int sum(0);
  int count(0);

  char value(it->current());
  it->next();

  while (!it->is_done() && sum < value)
  {
    sum += it->current();
    count++;
    it->next();
  }

  return (sum == value) ? count : 0;
}
