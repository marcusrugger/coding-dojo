#ifndef __KATA_ITERATOR_H__
#define __KATA_ITERATOR_H__

#include <stack>

#include "kata.char-decrement-iterator.h"


class KataIterator
{
public:


private:

  const char *_cur_ptr;
  const char *_end_ptr;
  const char *_inner_loop_end;
  bool _is_done;

  solution_stack *_stack;


public:

  KataIterator(const char *start,
               const char *end,
               const char *inner_loop_end,
               solution_stack *stack);


public: /* KataIterable interface */

  std::unique_ptr<CharDecrementIterator> next(void);
  void push_match_count(int count);

};


#endif  // __KATA_ITERATOR_H__
