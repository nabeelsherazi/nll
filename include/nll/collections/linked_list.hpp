#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>

#include <fmt/core.h>

namespace nll {

/// @brief Sequence container with O(1) push/pop from front, O(n) from back
template <class T>
class SinglyLinkedList {
 private:
  /// @brief Internal list node class
  struct ListNode {
    T value;
    ListNode* next;
    ListNode(T value) : value(value), next(nullptr) {};
  };

  ListNode* head;

  std::size_t size;

 public:
  /// @brief Iterator type for class
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Iterator(ListNode* ptr) : ptr(ptr) {};

    reference operator*() const { return this->ptr->value; };

    pointer operator->() { return this->ptr.value; };

    Iterator& operator++() {
      this->ptr = this->ptr->next;
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
    ListNode* ptr;
  };

  SinglyLinkedList() : head(nullptr), size(0) {};

  ~SinglyLinkedList() {
    while (this->head != nullptr) {
      auto oldHead = this->head;
      this->head = oldHead->next;
      delete oldHead;
    }
  }

  Iterator begin() { return Iterator(this->head); };

  Iterator end() { return Iterator(nullptr); }

  /// @brief Gets the current size of the list
  /// @return The current number of items in the list
  std::size_t Size() { return this->size; }

  T& operator[](int index) {
    if (index >= this->Size()) {
      throw std::logic_error(
          fmt::format("index {} is out of bounds for list of size {}", index,
                      this->Size()));
    }
    if (index < 0) {
      throw std::logic_error(
          fmt::format("negative index {} is not allowed!", index));
    }
    auto currentNode = this->head;
    for (auto i = 0; i < index; i++) {
      currentNode = currentNode->next;
    }
    return currentNode->value;
  }

  /// @brief Push a value to the front of the list (index 0). O(1) operation
  /// @param value the value to push
  void PushFront(T value) {
    ListNode* newNode = new ListNode(value);
    if (newNode) {
      newNode->next = head;
      this->head = newNode;
      this->size++;
    }
  }

  /// @brief Get the value at
  /// @return
  T PeekFront() {
    if (this->head) {
      return this->head->value;
    }
    throw std::runtime_error("list is empty!");
  }

  T PopFront() {
    if (this->head) {
      auto oldHead = this->head;
      auto val = oldHead->value;
      this->head = this->head->next;
      delete oldHead;
      return val;
    }
    throw std::runtime_error("list is empty!");
  }
};
}  // namespace nll