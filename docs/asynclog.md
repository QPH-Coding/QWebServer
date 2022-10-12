# Asynchronous Log System

## Overview

The Asynchronous Log System have features as follows:

- Accurate to subtlety

- Log the thread id

- Log line have level

- Log the source file and code line

- Thread safe

## Difference between SynchronousLog and AsynchronousLog

- Synchronous Log System's work flow: `make log line->obtain the mutex->write to file`
- Asynchronous Log System's work flow: `make log line->obtain the mutex->write to buffer`

The most important difference between Synchronous Log System(abbreviated as SyncLog) and Asynchronous Log System(abbreviated as AsyncLog) is that, SyncLog need write to the log file by itself after obtaining the mutex, the AsyncLog just write to buffer after obtaining the mutex. As we all know, the speed of the file I/O operation is much lower than the speed of writing to buffer in the program. In the case of high concurrency, the SyncLog will block other thread/process write log. The advantage of the AsyncLog is that it needn't do file I/O operation, just write log line to the buffer of the Log System. It's more efficient than SyncLog.

## Design

The Async Log System uses the idea of double buffers. One is called `forward buffer`, the other one is called `backward buffer`. 

Here is the blueprint:

![](assets/double-buffer.drawio.png)

The concrete code realization uses two buffer queues, one stores empty buffers called `empty queue`, the other stores full buffers called `full queue`.

One of the most important thing of the timing of the SWAP.

There are 2 moment that should swap two buffer:

- After a fixed period of time

- After a buffer become full

In this Async Log System, the actual swap operation is enqueue the `forward buffer` to the `full queue`. It will use POSIX semaphore to awake the backward work thread and get another empty buffer from `empty queue`.

However, if the `empty queue` has no empty buffer, how should we do? In my design, one buffer size is 2 MB and the initial buffer num is 5. It mean that have total 10 MB size to write log in a period of time. If the `empty queue` has no buffer, it probably has some problem make it produce too many log repeatedly. In this condition, just throw these log.

## Usage

Just use the `#define` in the head file.

The reason I use `#define` is that, when using `#define` you can judge the level in the current program stack and it simply use `__FILE__` and `__LINE__` to log the name of the source file and code line.