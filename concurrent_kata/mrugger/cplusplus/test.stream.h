#ifndef __TEST_STREAM_H__
#define __TEST_STREAM_H__

#include <queue>
#include <string>

#include "interface.kata-iterable.h"


class TestStream : public KataStream
{
private:

  std::string _sequence;
  unsigned int _replication_count;
  unsigned int _current_position;
  unsigned int _total_sequence_length;


public:

  TestStream(std::string &sequence, unsigned int replication_count);


public: /* KataStream inteface */

  virtual unsigned int readbytes(unsigned int count, char *block);
  virtual void rewind(unsigned int count);
  virtual bool is_eof(void);


private:

  unsigned int copy_next_block(unsigned int count, char *block);

};


#endif  // __TEST_STREAM_H__
