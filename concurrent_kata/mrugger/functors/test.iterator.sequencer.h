#pragma once
#include <string>
#include "test.iterator.iterators.h"


class sequencer
{
private:

  const char *_sequence;
  const std::size_t _sequence_length;

  const int _start_idx;
  const int _end_idx;

public:

  sequencer(const std::string sequence, unsigned int replication_count)
  : _sequence(sequence.c_str()),
    _sequence_length(sequence.length()),
    _start_idx(0),
    _end_idx(_sequence_length * replication_count)
  {}

  char operator()(int idx) const;

  char_iterator get_char_iterator(void) const;
  sequencer clone_front_half(void) const;
  sequencer clone_back_half() const;
  int length(void) const;


private:

  sequencer(const sequencer &other, int start, int end)
  : _sequence(other._sequence),
    _sequence_length(other._sequence_length),
    _start_idx(start),
    _end_idx(end)
  {}

};
