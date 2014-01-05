#ifndef __KATA_BLOCK_ITERATOR_H__
#define __KATA_BLOCK_ITERATOR_H__

#include <queue>
#include <mutex>

#include "kata.kata-iterator.h"


class BlockIterator
{
public:


private:

  unsigned int _block_size;
  const char *_current_block;
  const char *_begin_of_sequence;
  const char *_end_of_sequence;
  solution_queue *_queue;

  bool _is_done;
  std::mutex mtx;


public:

  BlockIterator(std::string &sequence, unsigned int block_size, solution_queue *queue);


public: /* BlockIterable interface */

  std::unique_ptr<KataIterator> next(void);

};


#endif  // __KATA_BLOCK_ITERATOR_H__
