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

  virtual char next(void) = 0;

};


class SequenceIterable
{
public:

  virtual void for_each(std::function<int(CharIterable *)> lambda) = 0;

};


class StreamIterable
{
public:

  virtual void for_each(std::function<int(SequenceIterable *)> lambda) = 0;

};


class KataStream
{
public:

  virtual unsigned int readbytes(unsigned int count, char *block) = 0;
  virtual void rewind(unsigned int count) = 0;
  virtual bool is_eof(void) = 0;

};


#endif  // __INTERFACE_KATA_ITERABLE_H__
