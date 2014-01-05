#include <cassert>
#include "kata.worker.h"


void KataWorker::find_all_solutions(BlockIterable *block_it)
{
  assert(block_it != NULL);

  std::unique_ptr<SequenceIterable> sequence_it(block_it->next());
  while (sequence_it.get() != NULL)
  {
    find_solutions(sequence_it.get());
    sequence_it.reset(block_it->next().release());
  }
}


void KataWorker::find_solutions(SequenceIterable *sequence_it)
{
  assert(sequence_it != NULL);
  
  std::unique_ptr<CharIterable> char_it(sequence_it->next());
  while (char_it.get() != NULL)
  {
    int count = match_count(char_it.get());
    sequence_it->push_match_count(count);
    char_it.reset(sequence_it->next().release());
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
    count++;
    it->next();
  }

  return (sum == value) ? count : 0;
}
