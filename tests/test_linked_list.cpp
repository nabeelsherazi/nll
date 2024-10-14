#include "nll/collections/linked_list.hpp"

#include <algorithm>
#include <stdexcept>

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(SinglyLinkedListTest, Creation) {
  auto list = nll::SinglyLinkedList<int>();
  list.PushFront(1);
  // Expect value stored successfully
  EXPECT_EQ(list.PeekFront(), 1);
}

TEST(SinglyLinkedListTest, Storage) {
  auto list = nll::SinglyLinkedList<int>();
  list.PushFront(1);
  list.PushFront(2);
  list.PushFront(3);
  // Expect value stored successfully
  EXPECT_EQ(list.Size(), 3);
}

TEST(SinglyLinkedListTest, Removal) {
  auto list = nll::SinglyLinkedList<int>();
  list.PushFront(1);
  list.PushFront(2);
  list.PushFront(3);
  // Expect value stored successfully
  EXPECT_EQ(list.PopFront(), 3);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 1);
}

TEST(SinglyLinkedListTest, ThrowsIfPopWhileEmpty) {
  auto list = nll::SinglyLinkedList<int>();
  EXPECT_THROW(list.PopFront(), std::runtime_error);
}

TEST(SinglyLinkedListTest, ThrowsIfPeekWhileEmpty) {
  auto list = nll::SinglyLinkedList<int>();
  EXPECT_THROW(list.PeekFront(), std::runtime_error);
}

TEST(SinglyLinkedListTest, IsIterable) {
  auto list = nll::SinglyLinkedList<int>();
  list.PushFront(1);
  list.PushFront(2);
  list.PushFront(3);
  auto total = 0;
  for (auto& val : list) {
    total += val;
  }
  EXPECT_EQ(total, 6);
}

TEST(SinglyLinkedListTest, SearchableWithFindAlgorithm) {
  auto list = nll::SinglyLinkedList<int>();
  list.PushFront(1);
  list.PushFront(2);
  list.PushFront(3);

  auto found = std::find(list.begin(), list.end(), 2);
  EXPECT_NE(found, list.end());
  EXPECT_EQ(*found, 2);
}

TEST(SinglyLinkedListTest, SearchingEmptyListIsSane) {
  auto list = nll::SinglyLinkedList<int>();

  auto found = std::find(list.begin(), list.end(), 2);
  EXPECT_EQ(found, list.end());
}

TEST(SinglyLinkedListTest, CanIndex) {
  auto list = nll::SinglyLinkedList<int>();
  list.PushFront(1);
  list.PushFront(2);
  list.PushFront(3);

  EXPECT_EQ(list[1], 2);
}