#ifndef __THREADS_PARALLELIZE_H__
#define __THREADS_PARALLELIZE_H__

#include <mutex>
#include <queue>
#include <pthread.h>
#include <cmath>

#include "interface.kata-iterable.h"


template <class IT, class PARM, class RV>
class ThreadsRun
{
public:

  static ThreadsRun *create(IT *seq, PARM yield)
  {
    return new ThreadsRun(seq, yield);
  }

  RV *join(void)
  {
    void *p;
    pthread_join(_thread, &p);
    return static_cast<RV *>(p);
  }


private:

  IT *_seq;
  PARM _yield;
  pthread_t _thread;

  ThreadsRun(IT *seq, PARM yield)
  : _seq(seq),
    _yield(yield)
  {
    pthread_create(&_thread, NULL, pthread_callback, static_cast<void *>(this));
  }

  void *callback(void)
  {
    return _seq->for_each(_yield);
  }

  static void *pthread_callback(void *ptr)
  {
    ThreadsRun *obj = static_cast<ThreadsRun *>(ptr);
    return obj->callback();
  }

};


template <class IT, class PARM, class RV>
class ThreadsParallelizer
{
public:

  const int _core_count;
  const int _parallelizer_depth;

  ThreadsParallelizer(void)
  : _core_count(std::thread::hardware_concurrency()),
    _parallelizer_depth((int) (std::log2((double) _core_count)))
  {}

  std::queue<RV *> *run(IT *seq, PARM yield)
  {
    std::queue<RV *> *queue = new std::queue<RV *>();
    std::queue<std::unique_ptr<ThreadsRun<IT, PARM, RV>>> thread_pool;
    parallelizer(0, _parallelizer_depth, &thread_pool, seq, yield);

    while (!thread_pool.empty())
    {
      ThreadsRun<IT, PARM, RV> *t = thread_pool.front().get();
      RV *stack = t->join();
      queue->push(stack);
      thread_pool.pop();
    }

    return queue;
  }


private:

  void parallelizer(int depth,
                    int parallelizer_depth,
                    std::queue<std::unique_ptr<ThreadsRun<IT, PARM, RV>>> *thread_pool,
                    IT *seq,
                    PARM yield)
  {
    if (depth < parallelizer_depth)
    {
      IT *seq1 = seq->clone_front_half();
      parallelizer(depth+1, parallelizer_depth, thread_pool, seq1, yield);

      IT *seq2 = seq->clone_back_half();
      parallelizer(depth+1, parallelizer_depth, thread_pool, seq2, yield);
    }
    else
    {
      ThreadsRun<IT, PARM, RV> *t = ThreadsRun<IT, PARM, RV>::create((IT *) seq, yield);
      thread_pool->push(std::unique_ptr<ThreadsRun<IT, PARM, RV>>(t));
    }
  }

};


#endif  // __THREADS_PARALLELIZE_H__
