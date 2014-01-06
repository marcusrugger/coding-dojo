#ifndef __KATA_STREAM_ITERATOR_H__
#define __KATA_STREAM_ITERATOR_H__

#include <queue>
#include <mutex>

#include "interface.kata-iterable.h"


class StreamIterator : public BlockIterable
{
public:


private:

  std::unique_ptr<KataStream> _stream;
  unsigned int _block_size;
  solution_queue *_queue;

  std::mutex _mtx;


public:

  StreamIterator(std::unique_ptr<KataStream> stream,
                 unsigned int block_size,
                 solution_queue *queue);


public: /* BlockIterable interface */

  virtual std::unique_ptr<SequenceIterable> next(void);


private:

  bool is_done(void);

};


#endif  // __KATA_STREAM_ITERATOR_H__
