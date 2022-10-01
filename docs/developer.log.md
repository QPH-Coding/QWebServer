# Developer Log
## Log

## 2022.10.01

- 13:55:20: Finish Time Wheel. But I have no idea to test.

- 16:30:42: Fix the `Timer` bug, it can reset correctly now.

## 2022.09.30

- 23:58:03: Finish Async Log System. During the developing, I find I must create 2 thread to manage their timers separately and create a writer thread to write to a file. 

- The days after:

- maybe can optimize the Async Log System, add source file and code lines

- Time Wheel

- HTTP Connection

- Object Pool

## 2022.09.29

- 11:17:11: I learned about a better model: `mulitied-Reactor`, this model actually need two thread pools, one is `sub-Reactor` which is responsible for I/O operating, the other is `logic-operating`. So I think I should reduce coupling of the thread pool, redesign it.

- 15:23:49: I have redesign the `class ThreadPool`, now the Thread Pool have high **reusability**.

- 20:59:04: Finish `class Timer`(`timer_fd` + `epoll`)

The days after:

- Time Wheel

- Async Log System - `AsyncLog4Q` and Buffer

- HttpConnection - Http Request analyze and make Response

- Object Pool - Consider using Factory Pattern

## 2022.09.28

- 11:50:00: `Thread Pool` can work normally. When I debug and Log something, I notice a `thread safe Log` is very important. If I use `std::cout` or `printf` , the threads will race to write to the output stream, it will make the Log can not be read.

- 15:54:56: After reading the book of ChenShuo carefully. I think before I develop the Async Log System, I should develop the module as follows:

  - Buffer

  - Timer

  - File IO System

Future arrangement:

- File IO System: design a sort of File IO API, can be use by Log System

- Buffer: For Log System

- Timer: Use `timer_fd` and `epoll`(use the `EpollListener`) to design a timer.

- Time Stamp: A Time Manager to make the time right.

- Log System: The Log System will be make of: Buffer, Timer, and can use `regular expression` to analyze it.

### 2022.09.27

Summary: Today, I finish the thread pool first. But can not pass the unit test. I can not deal with some unknown bug, it make my program can only create 1 thread, and stop in place.

Future arrangement:

- `Thread`: Overload the `class Thread`, make it work as Java, it can be used by extend the `base class: class Thread`. Don't use `std::function<void ()>`, it make me feel lots of pain.

- `Thread Pool`: Redesign it. I want to design a *high availability* `Thread Pool class`. However, something wrong is beyond my ability. So I think in this project, the thread pool maybe use only once, maybe I should not make it such a high priority. 



## Bug Fixing

- Question: Template no define
  
  Solution: While use template to code, please make the function declaration and implementation in a file.

- Question: Async Log System can not use timer correctly

  Solution: use 2 thread manage theirs timers separately

- Question: Async Log System can not make their threads correctly

  Solution: can not use `Join()`, and must use `Detach()`, let the thread work itself

- Question: `fwrite()` can not write into the file

  Solution: must insert `fseek()`, insert it and work correctly.

- Question: `Timer` can not reset correctly.

  Solution: I use `stop()` and `start()` to do reset simply, but it can not work. After read `timerfd_settime()` carefully, I find I can use this function to reset the Timer instead of using `Stop()` and `Start()`. And now I think the Timer member function's name `Exit()`  more appropriate than `Stop()`