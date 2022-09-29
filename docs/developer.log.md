# Developer Log
## Log

## 2022.09.29

---

- 11:17:11: I learned about a better model: `mulitied-Reactor`, this model actually need two thread pools, one is `sub-Reactor` which is responsible for I/O operating, the other is `logic-operating`. So I think I should reduce coupling of the thread pool, redesign it.

- 15:23:49: I have redesign the `class ThreadPool`, now the Thread Pool have high **reusability**.

## 2022.09.28

---

- 11:50:00: `Thread Pool` can work normally. When I debug and log something, I notice a `thread safe log` is very important. If I use `std::cout` or `printf` , the threads will race to write to the output stream, it will make the log can not be read.

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

---

Summary: Today, I finish the thread pool first. But can not pass the unit test. I can not deal with some unknown bug, it make my program can only create 1 thread, and stop in place.

Future arrangement:

- `Thread`: Overload the `class Thread`, make it work as Java, it can be used by extend the `base class: class Thread`. Don't use `std::function<void ()>`, it make me feel lots of pain.

- `Thread Pool`: Redesign it. I want to design a *high availability* `Thread Pool class`. However, something wrong is beyond my ability. So I think in this project, the thread pool maybe use only once, maybe I should not make it such a high priority. 



## Bug Fixing

---

- Question: Template no define
  
  Solution: While use template to code, please make the function declaration and implementation in a file.

- 