#ifndef __KATA_WORKER_H__
#define __KATA_WORKER_H__


#include "kata.block-iterator.h"


class KataWorker
{
public: /* Types */

  static void find_all_solutions(BlockIterator *it);
  static void find_solutions(KataIterator *it);

  static int match_count(CharDecrementIterator *it);

};


#endif  // __KATA_WORKER_H__
