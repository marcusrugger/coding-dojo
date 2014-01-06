#include <cassert>
#include <stdexcept>
#include "kata.block-iterator.h"


BlockIterator::BlockIterator(std::unique_ptr<StreamIterable> stream_iterator)
: _stream_iterator(stream_iterator.release())
{
  assert(_stream_iterator.get() != NULL);
}


void BlockIterator::for_each(std::function<int(CharIterable *)> lambda)
{
  std::unique_ptr<SequenceIterable> sequence_it(_stream_iterator->next());
  while (sequence_it.get() != NULL)
  {
    sequence_it->for_each(lambda);
    sequence_it.reset(_stream_iterator->next().release());
  }
}
