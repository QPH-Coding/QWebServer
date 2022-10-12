# Timer

## Overview

The `Timer` is use series of functions about timerfd.

This `Timer` is used in Asynchronous Log System and TimeWheel. It means that this module is one of the most important in this project.

## Design

The Timer has a pure virtual function `OnTick()`, it will be called when the time is up.

The reason I choose series of functions about timerfd is that it can use epoll. It's a high efficient I/O reuse mechanism. In particular, it can be used more conveniently after I encapsulate the `EpollListener`.

## Usage

`Timer` has a pure virtual function, so it can not be instantiated.

You can use it by inheriting `Timer` and override the `OnTick()`.