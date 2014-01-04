#ifndef __KATA_DIVVY_H__
#define __KATA_DIVVY_H__

#include <string>
#include <stack>


class KataWorker
{
public: /* Types */

  struct solution_pair
  {
    solution_pair(char *p, int c) : position(p), count(c) {}
    char *position;
    int count;
  };

  typedef std::stack<solution_pair> solution_stack;


  static solution_stack find_solutions(char *numbers, int count);

  static int match_count(char *numbers);

};


#endif  // __KATA_DIVVY_H__
