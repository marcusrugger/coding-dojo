#pragma once

class sequencer;


class char_iterator
{
private:

  const sequencer &_sequencer;
  int _idx;

public:

  char_iterator(const sequencer &seq, int idx)
  : _sequencer(seq), _idx(idx)
  {}

  char_iterator(const char_iterator &other)
  : _sequencer(other._sequencer), _idx(other._idx)
  {}

  char operator()(void) const;
  char_iterator next(void) const;
  int to_i(void) const;

};
