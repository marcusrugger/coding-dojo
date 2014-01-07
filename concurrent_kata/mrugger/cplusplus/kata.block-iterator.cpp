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
  _stream_iterator->for_each( [lambda] (SequenceIterable *sequence_it) -> int
      { sequence_it->for_each(lambda); });
}
