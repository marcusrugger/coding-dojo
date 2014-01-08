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

};


#endif  // __KATA_WORKER_H__
