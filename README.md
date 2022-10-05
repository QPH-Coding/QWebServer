<h1 align="center"> QWebServer </h1>

<img src="docs/assets/QWebServer.png" align="center" alt="HEAD">

## OverView

`QWebServer` is a Linux high performance WebServer written in modern C++. 

QWebServer refers to the design concept of the `muduo` Net Library.

## Feature

- Multi-Reactor Model

- Half Sync / Half Async Heap Model

- Highly reusable Thread Pool

- Highly efficient Async Log System

- Object Pool manage assets

- Timer Wheel deal with inactive connection

- Formatted HTTP Request analyze and Response

## Development Environment

Here is the list of the environment of this project:

- CPU: Intel Xeon E5-2680 v2 (2) @ 2.799GHz

- OS: Ubuntu 20.04

- Memory: 2 GB

And before you run this project, please make sure:

- CMake 3.24.1 (can be lower)

- g++ 11 (at least support C++20)

- MySql 5.7 

- MySql-connector-c++

- ElasticSearch (TODO version) (Optional)

You can use this command to install `MySql-connector-c++` in Ubuntu 20.04:

```shell
$ sudo apt-get install mysql-client mysql-server libmysql++-dev 
```

```sql
CREATE TABLE `user` (
    `id` INT unsigned  NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(64) NOT NULL,
    `salt` CHAR(6) NOT NULL,
    `sha256` CHAR(64) NOT NULL,
    PRIMARY KEY (`id`),
    UNIQUE KEY `key_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
```

## TODO List

- HTTP 解析

- 线程池

- 配置类

- 日志系统

- 定时器

- MySql 连接

- ES 连接

