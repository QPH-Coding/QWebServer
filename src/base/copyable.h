//
// Created by 钱沛桦 on 2022/9/27.
//

#ifndef QWEBSERVER_SRC_BASE_COPYABLE_H_
#define QWEBSERVER_SRC_BASE_COPYABLE_H_
class Copyable {
 public:
  Copyable(const Copyable &) = default;
  Copyable &operator=(const Copyable &) = default;
};
#endif //QWEBSERVER_SRC_BASE_COPYABLE_H_
