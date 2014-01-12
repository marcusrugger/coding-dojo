#include "test.iterator.sequencer.h"


char sequencer::operator()(int idx) const
{
  if (idx >= 0 && idx < _end_idx)
    return _sequence[idx % _sequence_length] - '0';
  else
    return '\0';
}


char_iterator sequencer::get_char_iterator(void) const
{ return char_iterator((*this), _start_idx); }


sequencer sequencer::clone_front_half(void) const
{
  int new_end_idx = _start_idx + (_end_idx - _start_idx) / 2;
  return sequencer((*this), _start_idx, new_end_idx);
}


sequencer sequencer::clone_back_half() const
{
  int new_start_idx = _start_idx + (_end_idx - _start_idx) / 2;
  return sequencer((*this), new_start_idx, _end_idx);
}


int sequencer::length(void) const
{ return _end_idx - _start_idx; }
