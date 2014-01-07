#ifndef __TEST_UNBOUNDED_ITERATORS_H__
#define __TEST_UNBOUNDED_ITERATORS_H__


#include "interface.kata-iterable.h"


/**** TestCharUnboundedIterator ***************************************************************************************/

class TestCharUnboundedIterator : public CharIterable
{
private:

  std::string &_sequence;
  int _current_position;

public:

  TestCharUnboundedIterator(std::string &sequence, int start_position)
  : _sequence(sequence), _current_position(start_position)
  {}


public: /* CharIterable interface */

  virtual char next(void)
  {
    if (is_done()) return '\0';
    return _sequence[_current_position-- % _sequence.length()] - '0';;
  }


private:

  bool is_done(void)
  { return _current_position < 0; }

};


/**** TestSequenceUnboundedIterator ***********************************************************************************/

class TestSequenceUnboundedIterator : public SequenceIterable
{
private:

  std::string &_sequence;
  solution_stack *_stack;

  int _current_position;

public:

  TestSequenceUnboundedIterator(std::string &sequence, int replication_count, solution_stack *stack)
  : _sequence(sequence),
    _stack(stack),
    _current_position(sequence.length() * replication_count - 1)
  {}


public: /* KataIterable interface */

  virtual void for_each(std::function<int(CharIterable *)> lambda)
  {
    std::unique_ptr<CharIterable> it(next());
    while (it.get() != NULL)
    {
      int count = lambda(it.get());
      push_match_count(count);
      it.reset(next());
    }
  }


private:

  bool is_done(void)
  { return _current_position < 0; }


  CharIterable *next(void)
  {
    if (is_done()) return NULL;
    return new TestCharUnboundedIterator(_sequence, _current_position--);
  }


  void push_match_count(int count)
  {
    if (count)
    {
      const char *pos = &(_sequence.c_str()[_current_position+1]);
      _stack->push(solution_pair(pos, count));
    }
  }

};


#endif  // __KATA_UNBOUNDED_ITERATORS_H__
