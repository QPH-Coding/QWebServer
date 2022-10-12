# Thread Pool

## Overview

The Object Pool has these features:

- Use template

- Thread safe

- Support call member function as work thread function

## Design

The Thread Pool is used in the high concurrent quantity condition. 

The other thread enqueue the task to the thread pool, the threads that managed by thread pool will be awake, and deal with the task by competing.

When the num of tasks more than the max num we set(in this project, I set it 10000), I think it must have some things we don't want to happen, such as: attacked by someone or the concurrent quantity is out of the ability. So the thread pool deal with the new task in this condition is throw it away.

## Usage

Just confirm the type of the task, and input the function dealing with the task. After that, just enqueue the task, the thread in the Thread Pool will work automatically.