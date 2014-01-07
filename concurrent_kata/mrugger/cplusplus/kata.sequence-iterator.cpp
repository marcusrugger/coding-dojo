#include <cassert>
#include <stdexcept>
#include "kata.sequence-iterator.h"
#include "kata.char-decrement-iterator.h"


SequenceIterator::SequenceIterator(char *block,
                                   const char *start,
                                   const char *end,
                                   const char *inner_loop_end,
                                   solution_stack *stack)
: _block(block),
  _cur_ptr(start),
  _end_ptr(end),
  _inner_loop_end(inner_loop_end),
  _stack(stack),
  _is_done(false)
{
  assert(start != NULL);
  assert(end != NULL);
  assert(start >= end);
  assert(inner_loop_end != NULL);
  assert(stack != NULL);
}


SequenceIterator::SequenceIterator(const char *start,
                                   const char *end,
                                   const char *inner_loop_end,
                                   solution_stack *stack)
: _cur_ptr(start),
  _end_ptr(end),
  _inner_loop_end(inner_loop_end),
  _stack(stack),
  _is_done(false)
{
  assert(start != NULL);
  assert(end != NULL);
  assert(start >= end);
  assert(inner_loop_end != NULL);
  assert(stack != NULL);
}


void SequenceIterator::for_each(std::function<int(CharIterable *)> lambda)
{
  std::unique_ptr<CharIterable> it(next());
  while (it.get() != NULL)
  {
    int count = lambda(it.get());
    push_match_count(count);
    it.reset(next());
  }
}


CharIterable *SequenceIterator::next(void)
{
  if (_is_done) return NULL;

  CharIterable *rv = new CharDecrementIterator(_cur_ptr--, _inner_loop_end);
  _is_done = _cur_ptr < _end_ptr;
  return rv;
}


void SequenceIterator::push_match_count(int count)
{
  if (count)
    _stack->push(solution_pair(_cur_ptr+1, count));
}
