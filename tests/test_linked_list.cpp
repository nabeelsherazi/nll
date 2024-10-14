#include "nll/collections/linked_list.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

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

TEST(SinglyLinkedListTest, PushBackStoresValues) {
  auto list = nll::SinglyLinkedList<int>();
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);
  // Expect value stored successfully
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 3);
}

TEST(SinglyLinkedListTest, ThrowsIfPopWhileEmpty) {
  auto list = nll::SinglyLinkedList<int>();
  EXPECT_THROW(list.PopFront(), std::out_of_range);
}

TEST(SinglyLinkedListTest, ThrowsIfPeekWhileEmpty) {
  auto list = nll::SinglyLinkedList<int>();
  EXPECT_THROW(list.PeekFront(), std::out_of_range);
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

/*
Tests operator* and operator-> on the iterator class.
*/
TEST(SinglyLinkedListTest, CanAccessValueThroughIterator) {
  auto list = nll::SinglyLinkedList<std::string>();
  std::string s1("hello");
  std::string s2("friend");
  list.PushFront(s1);
  list.PushFront(s2);
  auto it = list.begin();
  EXPECT_EQ((*it).length(), 6);
  it++;
  EXPECT_EQ(it->length(), 5);
}