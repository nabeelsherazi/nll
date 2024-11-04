#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>

#include <fmt/core.h>

namespace nll {

/// @brief Sequence container with O(1) push/pop from front, O(1) push to back
/// (tail optimization), and O(n) pop from back
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

  ListNode* head = nullptr;

  ListNode* tail = nullptr;

  std::size_t size = 0;

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

  Iterator begin() { return Iterator(head); }

  Iterator end() { return Iterator(nullptr); }

  const Iterator cbegin() { return Iterator(head); }

  const Iterator cend() { return Iterator(nullptr); }

  /// @brief Gets the current size of the list
  /// @return The current number of items in the list
  std::size_t Size() { return size; }

  /// @brief Returns whether the list is empty or not
  /// @return true if the list if empty
  bool Empty() { return Size() == 0; }

  /// @brief Deletes all elements from the list
  void Clear() {
    while (head) {
      auto old_head = head;
      head = old_head->next;
      delete old_head;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  /// @brief Index operator
  /// @param index
  /// @return item at given index
  /// @throws std::out_of_range if index is negative or >= size
  T& operator[](int index) {
    if (index >= Size()) {
      throw std::out_of_range(fmt::format(
          "index {} is out of bounds for list of size {}", index, Size()));
    }
    if (index < 0) {
      throw std::out_of_range(
          fmt::format("negative index {} is not allowed!", index));
    }
    // Tail optimization
    if (index == Size() - 1) {
      return tail->value;
    }
    auto currentNode = head;
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
    newNode->next = head;
    head = newNode;
    if (!tail) {
      tail = head;
    }
    size++;
  }

  /// @brief Returns the front element of the list without removing it.
  /// @returns the value at the front.
  /// @throws std::out_of_range if the list is empty.
  T& PeekFront() {
    if (head) {
      return head->value;
    }
    throw std::out_of_range("list is empty!");
  }

  /// @brief Returns the back element of the list without removing it.
  /// @returns the value at the back.
  /// @throws std::out_of_range if the list is empty.
  T& PeekBack() {
    if (tail) {
      return tail->value;
    }
    throw std::out_of_range("list is empty!");
  }

  /// @brief Removes and returns the front element of the list.
  /// @returns the value at the front.
  /// @throws std::out_of_range if the list is empty.
  T PopFront() {
    if (head) {
      auto old_head = head;
      auto val = old_head->value;
      if (tail == head) {
        tail = nullptr;
      }
      head = head->next;
      delete old_head;
      size--;
      return val;
    }
    throw std::out_of_range("list is empty!");
  }

  /// @brief Removes and returns the back element of the list.
  /// @returns the value at the back.
  /// @throws std::out_of_range if the list is empty.
  T PopBack() {
    if (head) {
      // Case head is the only node
      if (!head->next) {
        return PopFront();
      }
      auto lastNode = head;
      auto currentNode = head->next;
      while (currentNode->next) {
        lastNode = currentNode;
        currentNode = currentNode->next;
      }
      auto val = currentNode->value;
      lastNode->next = nullptr;
      tail = lastNode;
      delete currentNode;
      size--;
      return val;
    }
    throw std::out_of_range("list is empty!");
  }

  /// @brief Push a value to the back of the linked list. O(n) operation.
  /// @param value the value to push
  template <class U>
  void PushBack(U&& value) {
    if (!head) {
      return PushFront(std::forward<U>(value));
    }
    auto newNode = new ListNode(std::forward<U>(value));
    tail->next = newNode;
    tail = newNode;
    size++;
  }

  void Remove(T item) {
    if (!head) {
      throw std::out_of_range("list is empty!");
    }
    // Case remove head
    if (head->value == item) {
      PopFront();
      return;
    }
    // Case somewhere between
    ListNode* lastNode = head;
    ListNode* currentNode = head->next;
    while (currentNode) {
      if (currentNode->value == item) {
        lastNode->next = currentNode->next;
        if (currentNode == tail) {
          tail = lastNode;
        }
        delete currentNode;
        size--;
        return;
      }
      lastNode = currentNode;
      currentNode = currentNode->next;
    }
    throw std::out_of_range("item was not found in list!");
  };
};
}  // namespace nll