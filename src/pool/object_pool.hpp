// Author: QPH-Coding
// Create: 2022/10/3
// File: object_pool.hpp
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_POOL_OBJECT_POOL_HPP_
#define QWEBSERVER_SRC_POOL_OBJECT_POOL_HPP_

#include <vector>
#include <queue>
#include <mutex>
#include <functional>

// TODO
// en:
// Try to reconstruct the Object Pool
// get_one() return a Object<T>, not a T
// obviously, it is not convenient and elegant
// zh:
// 可以尝试重构对象池
// get_one()返回的是一个Object<T>，而不是一个T
// 很显然，这不方便，也不优美

// en:
// class Object the Object Pool use
// store the Object-T and the index in the Object Pool
// zh:
// 对象池使用的Object类
// 存储对象 T 及其在对象池中的索引
template<typename T>
class Object {
 public:
  Object(int index, const T &object);
  T &get_object();
  int get_index();
 private:
  T object_;
  int index_;
};

// TODO
// en: In modern C++, I think should not appear the raw pointer and exposed call the new/delete function
// zh: 在现代的C++中，我认为不应该出现裸露的指针及暴露地使用new/delete函数

// en:
// high reusable Object Pool
// use a std::vector store the pointer of object and a std::queue store indexes of the free object
// if you want to customize init and destruct object-T
// you can input the 2 more parameters: init_func_ and destruct_func_
// zh:
// 高可用的对象池
// 使用了std::vector存储对象的指针还有std::queue存储空闲对象的索引
// 如果你想定制化对象的初始化和对象析构前的动作
// 你可以额外传入2个参数: init_func_ 和 destruct_func_
template<typename T>
class ObjectPool {
 public:
  explicit ObjectPool(int init_num);
  explicit ObjectPool(int init_num, std::function<void(T &)> init_function, std::function<void(T &)> destruct_function);
  ~ObjectPool();
  Object<T> &get_one();
  void give_back_one(Object<T> object);
 private:
  std::mutex mutex_;
  std::vector<Object<T> *> objects_;
  std::queue<int> free_objects_;
  std::function<void(T &)> init_func_ = nullptr;
  std::function<void(T &)> destruct_func_ = nullptr;
};

template<typename T>
Object<T>::Object(int index, const T &object)
    :index_(index), object_(object) {
}
template<typename T>
T &Object<T>::get_object() {
  return object_;
}
template<typename T>
int Object<T>::get_index() {
  return index_;
}

template<typename T>
ObjectPool<T>::ObjectPool(int init_num) {
  for (int i = 0; i < init_num; ++i) {
    T raw_object;
    auto *object = new Object<T>(i, raw_object);
    objects_.push_back(object);
    free_objects_.push(i);
  }
}

template<typename T>
ObjectPool<T>::ObjectPool(int init_num,
                          std::function<void(T &)> init_function,
                          std::function<void(T &)> destruct_function)
    :init_func_(init_function),
     destruct_func_(destruct_function) {
  for (int i = 0; i < init_num; ++i) {
    T raw_object;
    if (init_func_ != nullptr) {
      init_func_(raw_object);
    }
    auto *object = new Object<T>(i, raw_object);
    objects_.push_back(object);
    free_objects_.push(i);
  }
}

template<typename T>
Object<T> &ObjectPool<T>::get_one() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!free_objects_.empty()) {
    int free_index = free_objects_.front();
    free_objects_.pop();
    return *objects_[free_index];
  }
  auto object = new Object<T>(objects_.size(), T());
  objects_.push_back(object);
  return *object;
}

template<typename T>
void ObjectPool<T>::give_back_one(Object<T> object) {
  std::lock_guard<std::mutex> lock(mutex_);
  free_objects_.push(object.get_index());
}
template<typename T>
ObjectPool<T>::~ObjectPool() {
  for (auto &p_object : objects_) {
    if (destruct_func_ != nullptr) {
      destruct_func_(p_object->get_object());
    }
    delete p_object;
  }
}

#endif //QWEBSERVER_SRC_POOL_OBJECT_POOL_HPP_
