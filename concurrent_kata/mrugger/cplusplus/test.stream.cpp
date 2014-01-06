#include "test.stream.h"


TestStream::TestStream(std::string &sequence, unsigned int replication_count)
: _sequence(sequence),
  _replication_count(replication_count),
  _current_position(0),
  _total_sequence_length(sequence.length() * replication_count)
{}


unsigned int TestStream::readbytes(unsigned int count, char *block)
{
  unsigned int copy_count = copy_next_block(count, block);

  while (copy_count < count && !is_eof())
    copy_count += copy_next_block(count, block + copy_count);

  return copy_count;
}


void TestStream::rewind(unsigned int count)
{
  _current_position = (_current_position > count) ? _current_position - count : 0;
}


bool TestStream::is_eof(void)
{
  _current_position >= _total_sequence_length;
}


unsigned int TestStream::copy_next_block(unsigned int count, char *block)
{
  unsigned int begin_index = _current_position % _sequence.length();
  std::size_t copied = _sequence.copy(block, count, begin_index);
  _current_position += (unsigned int) copied;
  return copied;
}
