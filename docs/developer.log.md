
## Log

---

### 2022.09.27

---

Summary: Today, I finish the thread pool first. But can not pass the unit test. I can not deal with some unknown bug, it make my program can only create 1 thread, and stop in place.

Future arrangement：

- `Thread`: Overload the `class Thread`, make it work as Java, it can be used by extend the `base class: class Thread`. Don't use `std::function<void ()>`, it make me feel lots of pain.

- `Thread Pool`: Redesign it. I want to design a *high availability* `Thread Pool class`. However, something wrong is beyond my ability. So I think in this project, the thread pool maybe use only once, maybe I should not make it such a high priority. 

## 2022.09.28

---

Summary: 

- 11:50:00: `Thread Pool` can work normally. When I debug and log something, I notice a `thread safe log` is very important. If I use `std::cout` or `printf` , the threads will race to write to the output stream, it will make the log can not be read.

- 15:54:56: After reading the book of ChenShuo carefully. I think before I develop the Async Log System, I should develop the module as follows:
  
  - Buffer

  - Timer

  - File IO System

## Bug Fixing

---

- Question: Template no define
  
  Solution: While use template to code, please make the function declaration and implementation in a file.

- 