# 线程池

## 概述

线程池有以下的特点:

- 使用模版进行编程

- 线程安全

- 支持调用成员函数作为线程的工作函数

## 详细设计

线程池被用在高并发的场景下。

其他线程将任务排入线程池的工作队列中，线程池管理的工作线程被唤醒，并且通过竞争处理工作。

当任务的数量超过我们设定的最大值(在这个项目中，我将其设定为10000)，我认为一定是发生了一些我们不想看到的事情，比如: 被攻击了或者并发量超过预想的能力。所以在这种情况下，线程池处理新任务的动作就是将其扔掉。

## 使用

只需要确定任务的类型，并且传入相应的处理任务的函数。之后只需要往线程池内的工作队列放入任务，线程池内的线程将会自动地工作。