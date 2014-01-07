#ifndef __KATA_WORKER_H__
#define __KATA_WORKER_H__


#include "kata.unbounded-iterators.h"


class KataWorker
{
public: /* Types */

  static void find_solutions(KataUnboundedSequenceIterator *sequence_it)
  {
    sequence_it->for_each(match_count);
  }


  static int match_count(KataUnboundedCharIterator *it)
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

};


#endif  // __KATA_WORKER_H__
