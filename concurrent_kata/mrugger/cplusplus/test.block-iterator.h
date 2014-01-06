#ifndef __KATA_BLOCK_ITERATOR_H__
#define __KATA_BLOCK_ITERATOR_H__

#include <queue>
#include <mutex>

#include "interface.kata-iterable.h"


class TestBlockIterator : public StreamIterable
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

  TestBlockIterator(std::string &sequence,
                    unsigned int block_size,
                    solution_queue *queue);


public: /* BlockIterable interface */

  virtual std::unique_ptr<SequenceIterable> next(void);


private:

  const char *next_block_start(void)
  { return _current_block + _block_size - 1; }

  const char *next_block_end(void)
  { return _current_block; }

  const char *next_inner_loop_end(void)
  { return (_current_block - _begin_of_sequence) > 8 ? _current_block - 8 : _begin_of_sequence; }

  void increment_current_block_to_next_block(void);

};


#endif  // __KATA_BLOCK_ITERATOR_H__
