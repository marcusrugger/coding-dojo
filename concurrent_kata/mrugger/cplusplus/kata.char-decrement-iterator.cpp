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


char CharDecrementIterator::next(void)
{
  if (is_done()) return '\0';
  return (*_cur_ptr--) - '0';
}


bool CharDecrementIterator::is_done(void)
{
  return _cur_ptr < _end_ptr;
}
