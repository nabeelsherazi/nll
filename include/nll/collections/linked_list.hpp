#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>

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

    template <class U>
    explicit ListNode(U&& value)
        : value(std::forward<U>(value)), next(nullptr){};
  };

  ListNode* head_ = nullptr;

  std::size_t size_ = 0;

 public:
  /// @brief Iterator type for class
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    explicit Iterator(ListNode* ptr) : ptr(ptr) {};

    reference operator*() const { return ptr->value; };

    pointer operator->() { return &(ptr->value); };

    Iterator& operator++() {
      ptr = ptr->next;
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
    ListNode* ptr = nullptr;
  };

  ~SinglyLinkedList() { Clear(); }

  Iterator begin() { return Iterator(head_); };

  Iterator end() { return Iterator(nullptr); }

  /// @brief Gets the current size_ of the list
  /// @return The current number of items in the list
  std::size_t Size() { return size_; }

  /// @brief Returns whether the list is empty or not
  /// @return true if the list if empty
  bool Empty() { return Size() == 0; }

  /// @brief Deletes all elements from the list
  void Clear() {
    while (head_) {
      auto old_head = head_;
      head_ = old_head->next;
      delete old_head;
    }
  }

  /// @brief Index operator
  /// @param index
  /// @return item at given index
  /// @throws std::out_of_range if index is negative or >= size
  T& operator[](int index) {
    if (index >= Size()) {
      throw std::out_of_range(fmt::format(
          "index {} is out of bounds for list of size_ {}", index, Size()));
    }
    if (index < 0) {
      throw std::out_of_range(
          fmt::format("negative index {} is not allowed!", index));
    }
    auto currentNode = head_;
    for (auto i = 0; i < index; i++) {
      currentNode = currentNode->next;
    }
    return currentNode->value;
  }

  /// @brief Push a value to the front of the list (index 0). O(1) operation
  /// @param value the value to push
  template <class U>
  void PushFront(U&& value) {
    ListNode* newNode = new ListNode(std::forward<U>(value));
    newNode->next = head_;
    head_ = newNode;
    size_++;
  }

  /// @brief Returns the front element of the list without removing it.
  /// @returns the value at the front.
  /// @throws std::out_of_range if the list is empty.
  T& PeekFront() {
    if (head_) {
      return head_->value;
    }
    throw std::out_of_range("list is empty!");
  }

  /// @brief Removes and returns the front element of the list.
  /// @returns the value at the front.
  /// @throws std::out_of_range if the list is empty.
  T PopFront() {
    if (head_) {
      auto old_head = head_;
      auto val = old_head->value;
      head_ = head_->next;
      delete old_head;
      return val;
    }
    throw std::out_of_range("list is empty!");
  }

  /// @brief Push a value to the back of the linked list. O(n) operation.
  /// @param value the value to push
  template <class U>
  void PushBack(U&& value) {
    auto newNode = new ListNode(std::forward<U>(value));
    size_++;
    if (!head_) {
      head_ = newNode;
      return;
    }
    auto currentNode = head_;
    while (currentNode->next) {
      currentNode = currentNode->next;
    }
    currentNode->next = newNode;
  }

  void Remove(T item) {
    if (!head_) {
      throw std::out_of_range("list is empty!");
    }
    ListNode* lastNode = head_;
    // Case remove head
    if (head_->value == item) {
      head_ = head_->next;
      delete lastNode;
      size_--;
      return;
    }
    // Case somewhere between
    ListNode* currentNode = head_->next;
    while (currentNode) {
      if (currentNode->value == item) {
        lastNode->next = currentNode->next;
        delete currentNode;
        size_--;
        return;
      }
      lastNode = currentNode;
      currentNode = currentNode->next;
    }
    throw std::out_of_range("item was not found in list!");
  };
};
}  // namespace nll