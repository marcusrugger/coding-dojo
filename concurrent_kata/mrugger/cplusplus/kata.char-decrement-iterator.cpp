#include <cassert>
#include <stdexcept>
#include "kata.char-decrement-iterator.h"


CharDecrementIterator::CharDecrementIterator(const char *start, const char *end)
: _cur_ptr(start), _end_ptr(end)
{
  assert(start != NULL);
  assert(end != NULL);
  assert(start >= end);
}


char CharDecrementIterator::current(void)
{
  if (is_done())
    throw std::runtime_error("CharDecrementIterator::current: iterator out of range");

  return (*_cur_ptr) - '0';
}


void CharDecrementIterator::next(void)
{
  if (is_done())
    throw std::runtime_error("CharDecrementIterator::next: iterator out of range");

  _cur_ptr--;
}


bool CharDecrementIterator::is_done(void)
{
  return _cur_ptr < _end_ptr;
}
