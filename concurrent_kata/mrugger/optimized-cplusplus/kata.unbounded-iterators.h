#ifndef __TEST_UNBOUNDED_ITERATORS_H__
#define __TEST_UNBOUNDED_ITERATORS_H__


#include <mutex>
#include <stack>
#include <memory>


typedef std::pair<int, int> match_pair;
typedef std::stack<match_pair> match_stack;

class KataUnboundedSequencer;
class KataUnboundedSequenceIterator;
class KataUnboundedCharIterator;


/**** TestSequenceUnboundedIterator ***********************************************************************************/

class KataUnboundedSequencer
{
public:

  const char *_sequence;
  int _sequence_length;
  int _total_sequence_size;

  std::mutex _mtx;
  std::stack<match_pair> _stack;

  KataUnboundedSequencer(std::string &string, int replication_count)
  : _sequence(string.c_str()),
    _sequence_length(string.length()),
    _total_sequence_size(string.length() * replication_count)
  {}

public: /* Sequencer interface */

  char at(int idx)
  { return _sequence[idx % _sequence_length] - '0'; }
  
};


/**** KataUnboundedCharIterator ***************************************************************************************/

class KataUnboundedCharIterator
{
public:

  KataUnboundedSequencer *_sequencer;
  int _current_position;
  int _end_position;

public:

  KataUnboundedCharIterator(KataUnboundedSequencer *sequencer, int start, int end)
  : _sequencer(sequencer), _current_position(start), _end_position(end)
  {}


public: /* CharIterable interface */

  char next(void)
  {
    if (is_done()) return '\0';
    return _sequencer->at(_current_position--);
  }


private:

  bool is_done(void)
  { return _current_position < _end_position; }

};


/**** KataUnboundedSequenceIterator ***********************************************************************************/

class KataUnboundedSequenceIterator
{
public:

  std::stack<match_pair> *_stack;

  KataUnboundedSequencer *_sequencer;

  int _current_position;
  int _end_position;
  int _match_end;

public:

  KataUnboundedSequenceIterator(KataUnboundedSequencer *sequencer, std::stack<match_pair> *stack, int start, int end, int match_end)
  : _sequencer(sequencer),
    _stack(stack),
    _current_position(start),
    _end_position(end),
    _match_end(match_end)
  {}


public: /* KataIterable interface */

  void for_each(std::function<int(KataUnboundedCharIterator *)> yield)
  {
    std::unique_ptr<KataUnboundedCharIterator> it(next());
    while (it.get() != NULL)
    {
      int count = yield(it.get());
      push_match_count(count);
      it.reset(next());
    }
  }


private:

  bool is_done(void)
  { return _current_position < _end_position; }


  KataUnboundedCharIterator *next(void)
  {
    if (is_done()) return NULL;
    return new KataUnboundedCharIterator(_sequencer, _current_position--, _match_end);
  }


  void push_match_count(int count)
  {
    if (count)
      _stack->push(match_pair(_current_position+1, count));
  }

};

#endif  // __KATA_UNBOUNDED_ITERATORS_H__
