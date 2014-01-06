#ifndef __KATA_BLOCK_ITERATOR_H__
#define __KATA_BLOCK_ITERATOR_H__

#include <stack>

#include "interface.kata-iterable.h"


class BlockIterator : public SequenceIterable
{
public:


private:

  std::unique_ptr<StreamIterable> _stream_iterator;

  std::function<int(CharIterable *)> _lambda;


public:

  BlockIterator(std::unique_ptr<StreamIterable> stream_iterator);


public: /* KataIterable interface */

  virtual void for_each(std::function<int(CharIterable *)> lambda);

};


#endif  // __KATA_BLOCK_ITERATOR_H__
