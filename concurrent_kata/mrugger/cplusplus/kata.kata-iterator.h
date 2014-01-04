#ifndef __KATA_ITERATOR_H__
#define __KATA_ITERATOR_H__

#include <stack>

#include "interface.kata-iterable.h"


class KataIterator : public KataIterable
{
public:

  struct solution_pair
  {
    solution_pair(const char *p, int c) : position(p), count(c) {}
    const char *position;
    int count;
  };

  typedef std::stack<solution_pair> solution_pair_stack;


private:

  const char *_cur_ptr;
  const char *_end_ptr;
  bool _is_done;

  solution_pair_stack _stack;


public:

  KataIterator(const char *start, const char *end);

  solution_pair_stack &stack(void);


public: /* KataIterable interface */

  virtual std::unique_ptr<CharIterable> current(void);
  virtual void next(void);
  virtual bool is_done(void);

  virtual void push_match_count(int count);

};


#endif  // __KATA_ITERATOR_H__
