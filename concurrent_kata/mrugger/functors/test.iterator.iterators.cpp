#include "test.iterator.iterators.h"
#include "test.iterator.sequencer.h"


char char_iterator::operator()(void) const
{ return _sequencer(_idx); }


char_iterator char_iterator::next(void) const
{ return char_iterator(_sequencer, _idx-1); }


int char_iterator::to_i(void) const
{ return _idx; }
