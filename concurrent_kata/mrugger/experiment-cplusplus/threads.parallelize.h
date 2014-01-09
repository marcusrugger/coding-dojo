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

  IT *_seq;
  PARM _yield;
  pthread_t _thread;


  ThreadsRun(IT *seq, PARM yield)
  : _seq(seq),
    _yield(yield)
  {}


  void run(void)
  {
    pthread_create(&_thread, NULL, moronic_pthread_crap, static_cast<void *>(this));
  }


  match_stack *join(void)
  {
    void *p;
    pthread_join(_thread, &p);
    return static_cast<RV *>(p);
  }


  static void *moronic_pthread_crap(void *ptr)
  {
    ThreadsRun *obj = static_cast<ThreadsRun *>(ptr);
    RV *stack = obj->_seq->for_each(obj->_yield);
    return stack;
  }

};


template <class IT, class PARM, class RV>
class ThreadsParallelizer
{
public:

  const int _core_count;
  const int _parallelizer_depth;

  ThreadsParallelizer(int core_count)
  : _core_count(core_count),
    _parallelizer_depth((int) (std::log2((double) core_count)))
  {}

  std::queue<RV *> *parallelize(IT *seq, PARM yield)
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
      ThreadsRun<IT, PARM, RV> *t = new ThreadsRun<IT, PARM, RV>((IT *) seq, yield);
      t->run();
      thread_pool->push(std::unique_ptr<ThreadsRun<IT, PARM, RV>>(t));
    }
  }

};


#endif  // __THREADS_PARALLELIZE_H__
