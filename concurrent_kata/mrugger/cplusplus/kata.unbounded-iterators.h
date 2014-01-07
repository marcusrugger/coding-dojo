#ifndef __TEST_UNBOUNDED_ITERATORS_H__
#define __TEST_UNBOUNDED_ITERATORS_H__


#include <mutex>
#include "interface.kata-iterable.h"


typedef std::pair<int, int> match_pair;
typedef std::stack<match_pair> match_stack;


/**** KataUnboundedCharIterator ***************************************************************************************/

class KataUnboundedCharIterator : public CharIterable
{
public:

  Sequencer *_sequence;
  int _current_position;
  int _end_position;

public:

  KataUnboundedCharIterator(Sequencer *sequence, int start, int end)
  : _sequence(sequence), _current_position(start), _end_position(end)
  {}


public: /* CharIterable interface */

  virtual char next(void)
  {
    if (is_done()) return '\0';
    return _sequence->at(_current_position--);
  }


private:

  bool is_done(void)
  { return _current_position < _end_position; }

};


/**** KataUnboundedSequenceIterator ***********************************************************************************/

class KataUnboundedSequenceIterator : public SequenceIterable
{
public:

  std::stack<match_pair> *_stack;

  Sequencer *_sequence;

  int _current_position;
  int _end_position;
  int _match_end;

public:

  KataUnboundedSequenceIterator(Sequencer *sequence, std::stack<match_pair> *stack, int start, int end, int match_end)
  : _sequence(sequence),
    _stack(stack),
    _current_position(start),
    _end_position(end),
    _match_end(match_end)
  {}


public: /* KataIterable interface */

  virtual void for_each(std::function<int(CharIterable *)> yield)
  {
    std::unique_ptr<CharIterable> it(next());
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


  CharIterable *next(void)
  {
    if (is_done()) return NULL;
    return new KataUnboundedCharIterator(_sequence, _current_position--, _match_end);
  }


  void push_match_count(int count)
  {
    if (count)
      _stack->push(match_pair(_current_position+1, count));
  }

};


/**** TestSequenceUnboundedIterator ***********************************************************************************/

class KataUnboundedSequencer : public Sequencer
{
public:

  std::string _sequence;
  int _total_sequence_size;

  std::mutex _mtx;
  std::stack<match_pair> _stack;

  KataUnboundedSequencer(std::string string, int replication_count)
  : _sequence(string), _total_sequence_size(string.length() * replication_count)
  {}

public: /* Sequencer interface */

  virtual char at(int idx)
  { return _sequence[idx % _sequence.length()] - '0'; }
  
};

#endif  // __KATA_UNBOUNDED_ITERATORS_H__
