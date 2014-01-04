#include <cassert>
#include <stdexcept>
#include "kata.kata-iterator.h"
#include "kata.char-decrement-iterator.h"


KataIterator::KataIterator(const char *start, const char *end)
: _cur_ptr(start), _end_ptr(end)
{}


KataIterator::solution_pair_stack &KataIterator::stack(void)
{
  return _stack;
}


std::unique_ptr<CharIterable> KataIterator::current(void)
{
  if (is_done())
    throw std::runtime_error("KataIterator::current: iterator out of range");

  return std::unique_ptr<CharDecrementIterator>(new CharDecrementIterator(_cur_ptr, _end_ptr));
}


void KataIterator::next(void)
{
  if (is_done())
    throw std::runtime_error("KataIterator::next: iterator out of range");

  _cur_ptr--;
}


bool KataIterator::is_done(void)
{
  return _cur_ptr < _end_ptr;
}


void KataIterator::push_match_count(int count)
{
  if (count)
    _stack.push(solution_pair(_cur_ptr, count));
}
