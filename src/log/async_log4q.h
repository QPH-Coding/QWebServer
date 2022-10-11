// Author: QPH-Coding
// Create: 2022/9/30
// File: async_log4q.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_LOG_ASYNC_LOG4Q_H_
#define QWEBSERVER_SRC_LOG_ASYNC_LOG4Q_H_

#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include "buffer.h"
#include <thread>
#include "../time/timer.h"
#include "../encapsulation/semaphore.h"
#include "../config/config.h"

#define AsyncLog4Q_Debug(content) if(AsyncLog4Q::get_level() <= AsyncLog4Q::Level::Debug) \
      AsyncLog4Q::Debug(content, __FILE__, __LINE__)
#define AsyncLog4Q_Info(content) if(AsyncLog4Q::get_level() <= AsyncLog4Q::Level::Info) \
      AsyncLog4Q::Info(content, __FILE__, __LINE__)
#define AsyncLog4Q_Warn(content) if(AsyncLog4Q::get_level() <= AsyncLog4Q::Level::Warn) \
      AsyncLog4Q::Warn(content, __FILE__, __LINE__)
#define AsyncLog4Q_Error(content) if(AsyncLog4Q::get_level() <= AsyncLog4Q::Level::Error) \
      AsyncLog4Q::Error(content, __FILE__, __LINE__)

// en:
// support 4 level
// use 3 thread to keep it in operation.
// buffer_timer_thread_: timing a period time to swap buffer
// time_stamp_timer_thread_: update timestamp every second
// write_to_file_thread_: write logs to file
// zh:
// 支持4个等级
// 使用3个线程来维持其运作
// buffer_timer_thread_: 负责计时一小段时间去交换缓冲
// time_stamp_timer_thread_: 每秒更新时间戳
// write_to_file_thread_: 将缓冲中的日志写入文件
class AsyncLog4Q {
 public:
  enum class Level {
    Debug = 0, Info = 1, Warn = 2, Error = 3
  };

  static void set_level(const Level &level) noexcept;
  static Level get_level() noexcept;

  static void Debug(const std::string &content);
  static void Debug(const std::string &content, const std::string &file, int line);
  static void Info(const std::string &content);
  static void Info(const std::string &content, const std::string &file, int line);
  static void Warn(const std::string &content);
  static void Warn(const std::string &content, const std::string &file, int line);
  static void Error(const std::string &content);
  static void Error(const std::string &content, const std::string &file, int line);

 private:
  AsyncLog4Q() noexcept;
  void Log(const Level &level, const std::string &content);

  void UpdateFileName() noexcept;

  void WriteBufferToFile();

  class TimeStampTimer : public Timer {
   public:
    TimeStampTimer() noexcept;
    void OnTick() override;
  };

  class BufferTimer : public Timer {
   public:
    explicit BufferTimer() noexcept;
    void OnTick() override;
  };

  class TimeStamp : private Uncopyable {
   public:
    static int year;
    static int month;
    static int day;
    static int hour;
    static int minute;
    static int second;
    static std::string get_date();
    static std::string get_time();
    static void Tick();
  };

  static AsyncLog4Q instance_;

  Level level_;
  std::string log_file_full_path_;
  std::string log_file_name_;

  BufferTimer buffer_timer_;
  TimeStampTimer time_stamp_timer_;
  std::thread buffer_timer_thread_;
  std::thread time_stamp_timer_thread_;
  std::thread write_to_file_thread_;

  std::mutex buffer_mutex_;
  std::mutex file_mutex_;
  Semaphore semaphore_;
  std::shared_ptr<Buffer> sp_curr_buffer_;
  std::queue<std::shared_ptr<Buffer>> empty_buffers_;
  std::queue<std::shared_ptr<Buffer>> full_buffers_;
};

#endif //QWEBSERVER_SRC_LOG_ASYNC_LOG4Q_H_
