#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

#include <fmt/core.h>

namespace nll {

/// @brief FIFO stack backed by a vector
template <class T>
class Stack {
  std::vector<T> stack;

 public:
  /// @brief Push a value to the top of the stack
  /// @param value the value to push
  template <class U>
  void Push(U&& value) {
    stack.push_back(std::forward<U>(value));
  }

  /// @brief Pop a value from the top of the stack
  /// @return the value at the top of the stack
  T Pop() {
    if (stack.empty()) {
      throw std::out_of_range("stack is empty!");
    }
    auto val = stack.back();
    stack.pop_back();
    return val;
  }

  /// @brief Peek at the value at the top of the stack
  /// @return the value at the top of the stack
  T Peek() {
    if (stack.Empty()) {
      throw std::out_of_range("stack is empty!");
    }
    return stack.back();
  }

  /// @brief Check if the stack is empty
  /// @return true if the stack is empty, false otherwise
  bool Empty() { return stack.empty(); }

  /// @brief Get the size of the stack
  /// @return the size of the stack
  std::size_t Size() { return stack.size(); }

  /// @brief Clear the stack
  void Clear() { stack.clear(); }

  /// @brief Iterator type for class
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    explicit Iterator(typename std::vector<T>::reverse_iterator ptr)
        : ptr(ptr) {};

    reference operator*() const { return *ptr; };

    pointer operator->() { return &(*ptr); };

    Iterator& operator++() {
      ++ptr;
      return *this;
    };

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.ptr == b.ptr;
    };

    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return a.ptr != b.ptr;
    };

   private:
    typename std::vector<T>::reverse_iterator ptr;
  };

  /// @brief Get an iterator to the beginning of the stack
  /// @return an iterator to the beginning of the stack
  Iterator begin() { return Iterator(stack.rbegin()); }

  /// @brief Get an iterator to the end of the stack
  /// @return an iterator to the end of the stack
  Iterator end() { return Iterator(stack.rend()); }

  /// @brief Get a const iterator to the beginning of the stack
  /// @return a const iterator to the beginning of the stack
  const Iterator cbegin() { return Iterator(stack.crbegin()); }

  /// @brief Get a const iterator to the end of the stack
  /// @return a const iterator to the end of the stack
  const Iterator cend() { return Iterator(stack.crend()); }
};

}  // namespace nll