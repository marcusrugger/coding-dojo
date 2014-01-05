#include <cassert>
#include <stdexcept>
#include "kata.kata-iterator.h"
#include "kata.char-decrement-iterator.h"


KataIterator::KataIterator(const char *start,
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


std::unique_ptr<CharIterable> KataIterator::next(void)
{
  if (_is_done)
    return std::unique_ptr<CharIterable>();

  std::unique_ptr<CharIterable> rv(new CharDecrementIterator(_cur_ptr--, _inner_loop_end));
  _is_done = _cur_ptr < _end_ptr;
  return rv;
}


void KataIterator::push_match_count(int count)
{
  if (count)
    _stack->push(solution_pair(_cur_ptr+1, count));
}
