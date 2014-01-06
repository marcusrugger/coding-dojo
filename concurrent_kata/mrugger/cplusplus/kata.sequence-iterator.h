#ifndef __KATA_ITERATOR_H__
#define __KATA_ITERATOR_H__

#include <stack>

#include "interface.kata-iterable.h"


class SequenceIterator : public SequenceIterable
{
public:


private:

  std::unique_ptr<char> _block;
  const char *_cur_ptr;
  const char *_end_ptr;
  const char *_inner_loop_end;
  bool _is_done;

  solution_stack *_stack;


public:

  SequenceIterator(char *block,
                   const char *start,
                   const char *end,
                   const char *inner_loop_end,
                   solution_stack *stack);

  SequenceIterator(const char *start,
                   const char *end,
                   const char *inner_loop_end,
                   solution_stack *stack);


public: /* KataIterable interface */

  virtual std::unique_ptr<CharIterable> next(void);
  virtual void push_match_count(int count);

};


#endif  // __KATA_ITERATOR_H__
