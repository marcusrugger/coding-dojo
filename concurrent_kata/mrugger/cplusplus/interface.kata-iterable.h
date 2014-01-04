#ifndef __INTERFACE_KATA_ITERABLE_H__
#define __INTERFACE_KATA_ITERABLE_H__

#include <memory>


class CharIterable
{
public:

  virtual char current(void) = 0;
  virtual void next(void) = 0;
  virtual bool is_done(void) = 0;

};


class KataIterable
{
public:

  virtual std::unique_ptr<CharIterable> current(void) {}
  virtual void next(void) {}
  virtual bool is_done(void) {}

  virtual void push_match_count(int count) {}

};


#endif  // __INTERFACE_KATA_ITERABLE_H__
