#ifndef __KATA_CHAR_DECREMENT_ITERATOR_H__
#define __KATA_CHAR_DECREMENT_ITERATOR_H__


#include "interface.kata-iterable.h"


class CharDecrementIterator : public CharIterable
{
private:

  const char *_cur_ptr;
  const char *_end_ptr;
  bool _is_done;


public:

  CharDecrementIterator(const char *start, const char *end);


public: /* CharIterable interface */

  virtual char current(void);
  virtual void next(void);
  virtual bool is_done(void);

};


#endif  // __KATA_CHAR_DECREMENT_ITERATOR_H__
