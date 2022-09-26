//
// Created by 钱沛桦 on 2022/9/26.
//

#ifndef QWEBSERVER_SRC_POOL_THREAD_POOL_H_
#define QWEBSERVER_SRC_POOL_THREAD_POOL_H_
#include <functional>
#include "../explanation/thread.h"

class ThreadPool {
  using workFunc = std::function<void()>;
 public:
  ThreadPool(int thread_num, workFunc &work_func);

 private:
  int thread_num_;
  Thread *pthread_;
};
#endif //QWEBSERVER_SRC_POOL_THREAD_POOL_H_
