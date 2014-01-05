#ifndef __KATA_CHAR_DECREMENT_ITERATOR_H__
#define __KATA_CHAR_DECREMENT_ITERATOR_H__


#include "interface.kata-iterable.h"


class CharDecrementIterator
{
private:

  const char *_cur_ptr;
  const char *_end_ptr;


public:

  CharDecrementIterator(const char *start, const char *end);


public: /* CharIterable interface */

  char current(void);
  void next(void);
  bool is_done(void);

};


#endif  // __KATA_CHAR_DECREMENT_ITERATOR_H__
