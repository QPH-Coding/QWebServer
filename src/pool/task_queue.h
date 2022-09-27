//
// Created by 钱沛桦 on 2022/9/26.
//

#ifndef QWEBSERVER_SRC_POOL_TASKQUEUE_H_
#define QWEBSERVER_SRC_POOL_TASKQUEUE_H_
#include <queue>
#include <mutex>

template<typename T>
class TaskQueue {
 public:
  TaskQueue() noexcept = default;
  void PushTask(const T &task) noexcept;
  T PopTask() const noexcept;
  int get_tasks_num() const noexcept;

 private:
  std::mutex mutex_;
  std::queue<T> tasks_;
};

#endif //QWEBSERVER_SRC_POOL_TASKQUEUE_H_
