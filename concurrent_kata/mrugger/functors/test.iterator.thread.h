#pragma once
#include <pthread.h>
#include <functional>
#include <list>
#include "test.iterator.sequencer.h"


typedef std::function<std::list<int>(const sequencer &, int)> thread_callback;


class mythread
{
public:

  static int MAX_TREE_DEPTH;

  mythread(thread_callback func, const sequencer &seq, int tree_depth);

  void run(void);
  std::list<int> join(void);


private:

  const sequencer &_seq;
  const thread_callback _func;
  const bool _spawn_thread;
  const int _tree_depth;
  pthread_t _thread;
  std::list<int> return_list;

  void *callback(void);
  static void *pthread_callback(void *ptr);

};
