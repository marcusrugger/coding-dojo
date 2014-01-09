#ifndef __INTERFACE_KATA_ITERABLE_H__
#define __INTERFACE_KATA_ITERABLE_H__

#include <memory>
#include <stack>
#include <queue>


typedef std::pair<int, int> match_pair;
typedef std::stack<match_pair> match_stack;
typedef std::queue<std::unique_ptr<match_stack>> match_queue;


class CharIterable
{
public:

  virtual char next(void) = 0;

};


class SequenceIterable
{
public:

  virtual match_stack *for_each(std::function<int(CharIterable *)> yield) = 0;

};


class Sequencer
{
public:

  virtual match_stack *for_each(std::function<match_stack *(SequenceIterable *)> yield) = 0;
  virtual char at(int idx) = 0;
  
};


#endif  // __INTERFACE_KATA_ITERABLE_H__
