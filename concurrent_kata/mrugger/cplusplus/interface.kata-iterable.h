#ifndef __INTERFACE_KATA_ITERABLE_H__
#define __INTERFACE_KATA_ITERABLE_H__

#include <memory>
#include <stack>
#include <queue>


struct solution_pair
{
  solution_pair(const char *p, int c) : position(p), count(c) {}
  const char *position;
  int count;
};

typedef std::stack<solution_pair> solution_stack;
typedef std::queue<std::unique_ptr<solution_stack>> solution_queue;


class CharIterable
{
public:

  virtual char current(void) = 0;
  virtual void next(void) = 0;
  virtual bool is_done(void) = 0;

};


class SequenceIterable
{
public:

  virtual std::unique_ptr<CharIterable> next(void) = 0;
  virtual void push_match_count(int count) = 0;

};


class BlockIterable
{
public:

  virtual std::unique_ptr<SequenceIterable> next(void) = 0;

};


#endif  // __INTERFACE_KATA_ITERABLE_H__
