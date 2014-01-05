#include <cassert>
#include <stdexcept>
#include "kata.kata-iterator.h"
#include "kata.block-iterator.h"


BlockIterator::BlockIterator(std::string &sequence, unsigned int block_size, solution_queue *queue)
: _current_block(sequence.c_str()),
  _begin_of_sequence(sequence.c_str()),
  _end_of_sequence(sequence.c_str() + sequence.length() - 1),
  _queue(queue),
  _is_done(false)
{
  assert(queue != NULL);
  _block_size = (block_size > 0) ? block_size : sequence.length();
}


std::unique_ptr<KataIterable> BlockIterator::next(void)
{
  const char *block_start(NULL);
  const char *block_end(NULL);
  const char *inner_end(NULL);
  solution_stack *block_stack(NULL);

  /* Mutex protected block */
  {
    std::lock_guard<std::mutex> lck(mtx);

    if (_is_done)
      return std::unique_ptr<KataIterable>();

    block_start = std::min(next_block_start(), _end_of_sequence);
    block_end   = next_block_end();
    inner_end   = next_inner_loop_end();
    block_stack = new solution_stack();

    _queue->push(std::unique_ptr<solution_stack>(block_stack));
    increment_current_block_to_next_block();
  }

  return std::unique_ptr<KataIterator>(new KataIterator(block_start, block_end, inner_end, block_stack));
}


void BlockIterator::increment_current_block_to_next_block(void)
{
  _current_block += _block_size;
  _is_done = _current_block > _end_of_sequence;
}
