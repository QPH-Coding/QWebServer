// Author: QPH-Coding
// Create: 2022/9/30
// File: async_log4q.cc
// License: Apache 2.0

#include <iostream>
#include "async_log4q.h"

AsyncLog4Q AsyncLog4Q::instance_ = AsyncLog4Q();

int AsyncLog4Q::TimeStamp::year = 0;
int AsyncLog4Q::TimeStamp::month = 0;
int AsyncLog4Q::TimeStamp::day = 0;
int AsyncLog4Q::TimeStamp::hour = 0;
int AsyncLog4Q::TimeStamp::minute = 0;
int AsyncLog4Q::TimeStamp::second = 0;

std::string AsyncLog4Q::TimeStamp::get_date() {
  std::string year_str, month_str, day_str;
  year_str = std::to_string(AsyncLog4Q::TimeStamp::year);
  if (AsyncLog4Q::TimeStamp::month < 10) {
    month_str = "0" + std::to_string(AsyncLog4Q::TimeStamp::month);
  } else {
    month_str = std::to_string(AsyncLog4Q::TimeStamp::month);
  }
  if (AsyncLog4Q::TimeStamp::day < 10) {
    day_str = "0" + std::to_string(AsyncLog4Q::TimeStamp::day);
  } else {
    day_str = std::to_string(AsyncLog4Q::TimeStamp::day);
  }
  return year_str + month_str + day_str;
}

std::string AsyncLog4Q::TimeStamp::get_time() {
  std::string hour_str, minute_str, second_str;
  if (AsyncLog4Q::TimeStamp::hour < 10) {
    hour_str = "0" + std::to_string(AsyncLog4Q::TimeStamp::hour);
  } else {
    hour_str = std::to_string(AsyncLog4Q::TimeStamp::hour);
  }
  if (AsyncLog4Q::TimeStamp::minute < 10) {
    minute_str = "0" + std::to_string(AsyncLog4Q::TimeStamp::minute);
  } else {
    minute_str = std::to_string(AsyncLog4Q::TimeStamp::minute);
  }
  if (AsyncLog4Q::TimeStamp::second < 10) {
    second_str = "0" + std::to_string(AsyncLog4Q::TimeStamp::second);
  } else {
    second_str = std::to_string(AsyncLog4Q::TimeStamp::second);
  }
  return hour_str + minute_str + second_str;
}

void AsyncLog4Q::TimeStamp::Tick() {
  ++second;
  if (second == 60) {
    second = 0;
    ++minute;
  }
  if (minute == 60) {
    minute = 0;
    ++hour;
  }
  if (hour == 24) {
    hour = 0;
    // en: use localtime instead of complex logical judgment
    // zh: 用localtime函数，而不是用一些复杂的逻辑判断
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    year = ltm->tm_year + 1900;
    month = ltm->tm_mon + 1;
    day = ltm->tm_mday;
    // TODO maybe can optimize
    instance_.UpdateFileName();
  }
}

AsyncLog4Q::AsyncLog4Q() noexcept
    : mutex_(std::mutex()),
      semaphore_(Semaphore()),
      buffer_timer_(BufferTimer()),
      time_stamp_timer_(TimeStampTimer()),
      level_(Level::Info) {
  sp_curr_buffer_.reset(new Buffer);
  empty_buffers_ = std::queue<std::shared_ptr<Buffer>>();
  for (int i = 0; i < 4; ++i) {
    empty_buffers_.push(std::make_shared<Buffer>());
  }
  full_buffers_ = std::queue<std::shared_ptr<Buffer>>();

  // en: Init the timestamp
  // zh: 初始化时间戳timestamp
  time_t now = time(nullptr);
  tm *ltm = localtime(&now);
  AsyncLog4Q::TimeStamp::year = ltm->tm_year + 1900;
  AsyncLog4Q::TimeStamp::month = ltm->tm_mon + 1;
  AsyncLog4Q::TimeStamp::day = ltm->tm_mday;
  AsyncLog4Q::TimeStamp::hour = ltm->tm_hour;
  AsyncLog4Q::TimeStamp::minute = ltm->tm_min;
  AsyncLog4Q::TimeStamp::second = ltm->tm_sec;

  // TODO dir choose can optimize, can write a shell instead it
  system("mkdir -p /server/log");
  UpdateFileName();

  buffer_timer_thread_ = std::thread([&] { buffer_timer_.Start(); });
  time_stamp_timer_thread_ = std::thread([&] { time_stamp_timer_.Start(); });
  write_to_file_thread_ = std::thread(&AsyncLog4Q::WriteBufferToFile, this);
  buffer_timer_thread_.detach();
  time_stamp_timer_thread_.detach();
  write_to_file_thread_.detach();
}

AsyncLog4Q::BufferTimer::BufferTimer() noexcept: Timer(3) {}

void AsyncLog4Q::BufferTimer::OnTick() {
  std::lock_guard<std::mutex> lock(instance_.mutex_);
  instance_.full_buffers_.push(instance_.sp_curr_buffer_);
  instance_.semaphore_.Signal();
  if (instance_.empty_buffers_.empty()) {
    instance_.sp_curr_buffer_ = nullptr;
    return;
  }
  instance_.sp_curr_buffer_ = instance_.empty_buffers_.front();
  instance_.empty_buffers_.pop();
}

void AsyncLog4Q::WriteBufferToFile() {
  while (true) {
    //  en:
    // semaphore_ add one means have one full buffer wait to write
    // zh:
    // semaphore_加一说明有一块写满的buffer要去写入文件
    semaphore_.Wait();
    FILE *write_file = fopen(log_file_full_path_.c_str(), "a");
    std::shared_ptr<Buffer> sp_write_buffer = full_buffers_.front();
    while (sp_write_buffer->WriteToFd(write_file, sp_write_buffer->size()) > 0) {}
    sp_write_buffer->Reset();
    {
      std::lock_guard<std::mutex> lock(mutex_);
      empty_buffers_.push(sp_write_buffer);
      full_buffers_.pop();
    }
    fclose(write_file);
  }
}

AsyncLog4Q::TimeStampTimer::TimeStampTimer() noexcept: Timer(1) {}

void AsyncLog4Q::TimeStampTimer::OnTick() {
  AsyncLog4Q::TimeStamp::Tick();
}

void AsyncLog4Q::Log(const AsyncLog4Q::Level &level, const std::string &content) {
  // en:
  // if sp_curr_buffer_ is nullptr and empty_buffers is empty
  // it means that some wrongs happen and have detected out it before
  // just keep throwing log_line away.
  // zh:
  // 如果sp_curr_buffer_是空指针，并且empty_buffers是空的,
  // 就说明有什么错误发生了，并且在之前已经检测出错误了
  // 在这里保持扔掉日志就可以了
  {
    std::lock_guard lock(mutex_);
    if (!sp_curr_buffer_) {
      if (empty_buffers_.empty()) {
        return;
      } else {
        sp_curr_buffer_ = empty_buffers_.front();
        empty_buffers_.pop();
      }
    }
  }


  // log_line format: ${date} ${time}.${nanosecond}Z ${level} ${content}
  // log_line example: "20220930 214950.513518Z INFO Hello world"
  // region make Log
  std::string log_line =
      AsyncLog4Q::TimeStamp::get_date() + " " +
          AsyncLog4Q::TimeStamp::get_time() + ".";
  timespec now{};
  clock_gettime(CLOCK_REALTIME, &now);
  std::string nsec_str = std::to_string(now.tv_nsec);
  if (nsec_str.length() > 6) {
    nsec_str = nsec_str.substr(0, 6);
  } else {
    nsec_str += std::string(6 - nsec_str.length(), '0');
  }
  log_line += nsec_str + " " + std::to_string(gettid()) + " ";

  if (level == AsyncLog4Q::Level::Debug) {
    log_line += "DEBUG";
  } else if (level == AsyncLog4Q::Level::Info) {
    log_line += "INFO";
  } else if (level == AsyncLog4Q::Level::Warn) {
    log_line += "WARN";
  } else if (level == AsyncLog4Q::Level::Error) {
    log_line += "ERROR";
  }
  log_line += " " + content + "\n";
  // endregion

  // TEST
  std::cout << log_line << std::endl;
  // en: while append current buffer, should lock the mutex_
  // zh: 当往当前的buffer写入东西时，需要加锁
  std::lock_guard<std::mutex> lock(mutex_);

  // en:
  // if try to append to buffer failed, get one from empty buffer queue
  // push full buffer to full buffer queue
  // if empty buffer queue is empty, it probably has some wrongs
  // and produce Log in some the same places
  // we just throw these Log
  // zh:
  // 如果尝试写入buffer失败，从空buffer队列中取出一块新的buffer
  // 往full buffer队列中放入当前的buffer
  // 如果空buffer队列空了，很有可能程序出现了问题，导致在某个地方产生日志
  // 对于这部分日志我们可以直接扔掉他们
  if (!sp_curr_buffer_->Append(log_line.c_str(), log_line.length())) {
    full_buffers_.push(sp_curr_buffer_);
    semaphore_.Signal();
    // en: after push a new full buffer, should reset the buffer timer
    // zh: 在放入一块新的full buffer后，要重置buffer的计时器
    buffer_timer_.Reset();

    if (empty_buffers_.empty()) {
      sp_curr_buffer_ = nullptr;
      return;
    }
    sp_curr_buffer_ = empty_buffers_.front();
    empty_buffers_.pop();
    sp_curr_buffer_->Append(log_line.c_str(), log_line.length());
  }
}

void AsyncLog4Q::Debug(const std::string &content) {
  if (instance_.level_ > Level::Debug) {
    return;
  }
  instance_.Log(Level::Debug, "'" + content + "'");
}

void AsyncLog4Q::Debug(const std::string &content, const std::string &file, const int line) {
  instance_.Log(Level::Debug, "'" + content + "' " + file + ":" + std::to_string(line));
}

void AsyncLog4Q::Info(const std::string &content) {
  if (instance_.level_ > Level::Info) {
    return;
  }
  instance_.Log(Level::Info, "'" + content + "'");
}

void AsyncLog4Q::Info(const std::string &content, const std::string &file, const int line) {
  instance_.Log(Level::Info, "'" + content + "' " + file + ":" + std::to_string(line));
}

void AsyncLog4Q::Warn(const std::string &content) {
  if (instance_.level_ > Level::Warn) {
    return;
  }
  instance_.Log(Level::Warn, "'" + content + "'");
}

void AsyncLog4Q::Warn(const std::string &content, const std::string &file, const int line) {
  instance_.Log(Level::Warn, "'" + content + "' " + file + ":" + std::to_string(line));
}

void AsyncLog4Q::Error(const std::string &content) {
  instance_.Log(Level::Error, "'" + content + "'");
}

void AsyncLog4Q::Error(const std::string &content, const std::string &file, const int line) {
  instance_.Log(Level::Error, "'" + content + "' " + file + ":" + std::to_string(line));
}

void AsyncLog4Q::set_level(const AsyncLog4Q::Level &level) noexcept {
  instance_.level_ = level;
}

void AsyncLog4Q::UpdateFileName() noexcept {
  // log_file_name format: QWebSever.${date}-${time}.${pid}.Log
  // log_file_name example: QWebServer.20220930-202826.10612.Log
  log_file_name_ = "QWebServer." +
      AsyncLog4Q::TimeStamp::get_date() +
      "-" +
      AsyncLog4Q::TimeStamp::get_time() +
      "." +
      std::to_string(Config::Pid()) + ".Log";
  log_file_full_path_ = Config::LogDirPath() + "/" + log_file_name_;
}
AsyncLog4Q::Level AsyncLog4Q::get_level() noexcept {
  return instance_.level_;
}



