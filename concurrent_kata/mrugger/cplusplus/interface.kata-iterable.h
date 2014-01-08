#ifndef __INTERFACE_KATA_ITERABLE_H__
#define __INTERFACE_KATA_ITERABLE_H__

#include <memory>
#include <stack>
#include <queue>


class CharIterable
{
public:

  virtual char next(void) = 0;

};


class SequenceIterable
{
public:

  virtual void for_each(std::function<int(CharIterable *)> yield) = 0;

};


class Sequencer
{
public:

  virtual char at(int idx) = 0;
  
};


#endif  // __INTERFACE_KATA_ITERABLE_H__
