#ifndef __KATA_WORKER_H__
#define __KATA_WORKER_H__


#include "interface.kata-iterable.h"


class KataWorker
{
public: /* Types */

  static void find_solutions(SequenceIterable *it);
  static int match_count(CharIterable *it);

};


#endif  // __KATA_WORKER_H__
