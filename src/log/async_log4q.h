// Author: QPH-Coding
// Create: 2022/9/30
// File: async_log4q.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_LOG_ASYNC_LOG4Q_H_
#define QWEBSERVER_SRC_LOG_ASYNC_LOG4Q_H_

#include <memory>
#include <mutex>
#include <queue>
#include "buffer.h"
#include "../explanation/thread.h"
#include "../time/timer.h"
#include "../explanation/semaphore.h"
#include "../config/config.h"

class AsyncLog4Q {
 public:
  enum class Level {
    Debug = 0, Info = 1, Warn = 2, Error = 4
  };

  static void Init() noexcept;

  static void SetLevel(const Level &level, AsyncLog4Q &async_log = instance_) noexcept;

  static void Debug(const std::string &content, AsyncLog4Q &async_log = instance_);
  static void Info(const std::string &content, AsyncLog4Q &async_log = instance_);
  static void Warn(const std::string &content, AsyncLog4Q &async_log = instance_);
  static void Error(const std::string &content, AsyncLog4Q &async_log = instance_);

 private:
  AsyncLog4Q() noexcept;
  void Log(const Level &level, const std::string &content);

  void UpdateFileName() noexcept;

  class BufferTimerThread : public Thread {
   public:
    explicit BufferTimerThread() noexcept;
    void Run() override;
    void Reset() noexcept;
   private:
    class BufferTimer : public Timer {
     public:
      explicit BufferTimer() noexcept;
      void OnTick() override;
    };
    BufferTimer buffer_timer_;
  };

  class TimeStampTimerThread : public Thread {
   public:
    explicit TimeStampTimerThread() noexcept;
    void Run() override;
   private:
    class TimeStampTimer : public Timer {
     public:
      TimeStampTimer() noexcept;
      void OnTick() override;
    };
    TimeStampTimer time_stamp_timer_;
  };

  class WriterThread : public Thread {
   public:
    void Run() override;
  };

  class TimeStamp : private Uncopyable {
   public:
    static int year;
    static int month;
    static int day;
    static int hour;
    static int minute;
    static int second;
    static std::string GetDate();
    static std::string GetTime();
    static void Tick();
  };

  static AsyncLog4Q instance_;

  Level level_;
  std::string log_file_full_path_;
  std::string log_file_name_;

  WriterThread writer_thread_;
  BufferTimerThread buffer_timer_thread_;
  TimeStampTimerThread time_stamp_timer_thread_;
  std::mutex mutex_;
  Semaphore semaphore_;
  std::shared_ptr<Buffer> sp_curr_buffer_;
  std::queue<std::shared_ptr<Buffer>> empty_buffers_;
  std::queue<std::shared_ptr<Buffer>> full_buffers_;
};

#endif //QWEBSERVER_SRC_LOG_ASYNC_LOG4Q_H_
