#ifndef __KATA_BLOCK_ITERATOR_H__
#define __KATA_BLOCK_ITERATOR_H__

#include <queue>
#include <mutex>

#include "interface.kata-iterable.h"


class BlockIterator : public BlockIterable
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

  virtual std::unique_ptr<KataIterable> next(void);


private:

  int next_block_start(void)
  { return _current_block + _block_size - 1; }

  int next_block_end(void)
  { return _current_block; }

  int next_inner_loop_end(void)
  { return (_current_block - _begin_of_sequence) > 8 ? _current_block - 8 : _begin_of_sequence; }

  int increment_current_block(void);

};


#endif  // __KATA_BLOCK_ITERATOR_H__
