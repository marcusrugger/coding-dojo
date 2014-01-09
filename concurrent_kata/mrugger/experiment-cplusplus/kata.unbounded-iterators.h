#ifndef __TEST_UNBOUNDED_ITERATORS_H__
#define __TEST_UNBOUNDED_ITERATORS_H__


#include <mutex>
#include "interface.kata-iterable.h"
#include "threads.parallelize.h"


/**** KataUnboundedCharIterator ***************************************************************************************/

class KataUnboundedCharIterator : public CharIterable
{
public:

  Sequencer *_sequencer;
  int _current_position;
  int _end_position;

public:

  KataUnboundedCharIterator(Sequencer *sequencer)
  : _sequencer(sequencer), _current_position(-1), _end_position(0)
  {}

  void reset(int start, int end)
  { _current_position = start; _end_position = end; }


public: /* CharIterable interface */

  virtual char next(void)
  {
    if (is_done()) return '\0';
    return _sequencer->at(_current_position--);
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

  Sequencer *_sequencer;

  std::unique_ptr<KataUnboundedCharIterator> _char_iterator;

  int _current_position;
  int _end_position;
  int _match_end;

public:

  KataUnboundedSequenceIterator(Sequencer *sequencer, int start, int end, int match_end)
  : _sequencer(sequencer),
    _current_position(start),
    _end_position(end),
    _match_end(match_end),
    _char_iterator(new KataUnboundedCharIterator(_sequencer))
  {}


public: /* KataIterable interface */

  virtual match_stack *for_each(std::function<int(CharIterable *)> yield)
  {
    std::unique_ptr<match_stack> stack(new match_stack());
    CharIterable *it;

    while (it = next())
      push_match_count(stack.get(), yield(it));

    return stack.release();
  }


private:

  bool is_done(void)
  { return _current_position < _end_position; }


  CharIterable *next(void)
  {
    if (is_done()) return NULL;
    _char_iterator->reset(_current_position--, _match_end);
    return _char_iterator.get();
  }


  void push_match_count(match_stack *stack, int count)
  {
    if (count)
    {
      printf("pushing match: %d, %d\n", _current_position+1, count);
      stack->push(match_pair(_current_position+1, count));
    }
  }

};


/**** TestSequenceUnboundedIterator ***********************************************************************************/
#include <pthread.h>
class KataUnboundedSequencer : public Sequencer
{
public:

  const char *_sequence;
  int _sequence_length;
  int _total_sequence_size;

  KataUnboundedSequencer(std::string &string, int replication_count)
  : _sequence(string.c_str()),
    _sequence_length(string.length()),
    _total_sequence_size(string.length() * replication_count),
    _range(0, _total_sequence_size-1)
  {}


  typedef std::pair<int, int> sequence_range;
  sequence_range _range;

  KataUnboundedSequencer(KataUnboundedSequencer *seq, bool front_half)
  : _sequence(seq->_sequence),
    _sequence_length(seq->_sequence_length),
    _total_sequence_size(seq->_total_sequence_size)
  {
    int len = seq->_range.second + 1 - seq->_range.first;
    int half = len / 2;

    if (front_half)
    {
      _range.first = seq->_range.first;
      _range.second = seq->_range.first + half - 1;
    }
    else
    {
      _range.first = seq->_range.first + half;
      _range.second = seq->_range.second;
    }
  }

public: /* ThreadDivisible interface */

  virtual KataUnboundedSequencer *clone_front_half(void)
  { return new KataUnboundedSequencer(this, true); }

  virtual KataUnboundedSequencer *clone_back_half(void)
  { return new KataUnboundedSequencer(this, false); }

public: /* Sequencer interface */

  virtual match_stack *for_each(std::function<match_stack *(SequenceIterable *)> yield)
  {
    printf("for_each: %d, %d\n", _range.first, _range.second);

    std::unique_ptr<SequenceIterable>
    it(new KataUnboundedSequenceIterator(this,
                                         _range.second,
                                         _range.first,
                                         _range.first == 0 ? 0 : _range.first - 8));
    return yield(it.get());
  }

  virtual char at(int idx)
  { return _sequence[idx % _sequence_length] - '0'; }

};

#endif  // __KATA_UNBOUNDED_ITERATORS_H__
