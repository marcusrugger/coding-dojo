#include <iostream>
#include <thread>
#include <chrono>
#include "test.iterator.thread.h"


mythread::mythread(thread_callback func, const sequencer &seq, int tree_depth)
: _func(func),
  _seq(seq),
  _tree_depth(tree_depth),
  _spawn_thread(tree_depth < MAX_TREE_DEPTH)
{
}


void mythread::run(void)
{
  if (_spawn_thread)
  {
    printf("New thread...\n");
    pthread_create(&_thread, NULL, pthread_callback, static_cast<void *>(this));
  }
  else
    return_list = _func(_seq, _tree_depth);
}


std::list<int> mythread::join(void)
{
  if (_spawn_thread) pthread_join(_thread, NULL);
  return return_list;
}


void *mythread::callback(void)
{
  return_list = _func(_seq, _tree_depth);
  std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "Thread done: " << ctime(&tt);
  return NULL;
}


void *mythread::pthread_callback(void *ptr)
{
  mythread *obj = static_cast<mythread *>(ptr);
  return obj->callback();
}
