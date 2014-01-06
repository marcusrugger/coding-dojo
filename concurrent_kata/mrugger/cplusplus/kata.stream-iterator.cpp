#include "kata.stream-iterator.h"
#include "kata.sequence-iterator.h"


StreamIterator::StreamIterator(std::unique_ptr<KataStream> stream,
                               unsigned int block_size,
                               solution_queue *queue)
: _stream(stream.release()),
  _block_size(block_size),
  _queue(queue)
{}


std::unique_ptr<SequenceIterable> StreamIterator::next(void)
{
  std::unique_ptr<char> next_block(new char[_block_size]);
  std::unique_ptr<solution_stack> block_stack(new solution_stack());
  solution_stack *stack = block_stack.get();
  char *start_position  = NULL;
  char *end_position    = NULL;
  char *inner_loop_end  = NULL;

  /* Mutex protected block */
  {
    std::lock_guard<std::mutex> lck(_mtx);

    if (is_done())
      return std::unique_ptr<SequenceIterable>();

    bool is_first_block = _queue->size() == 0;

    _stream->rewind(8);
    unsigned int bytes_read = _stream->readbytes(_block_size, next_block.get());
    _queue->push(std::unique_ptr<solution_stack>(block_stack.release()));

    start_position  = next_block.get() + bytes_read - 1;
    end_position    = is_first_block ? next_block.get() : next_block.get() + std::min(8u, bytes_read-1);
    inner_loop_end  = next_block.get();
  }

  return std::unique_ptr<SequenceIterable>(new SequenceIterator(next_block.release(), start_position, end_position, inner_loop_end, stack));
}


bool StreamIterator::is_done(void)
{
  return _stream->is_eof();
}
