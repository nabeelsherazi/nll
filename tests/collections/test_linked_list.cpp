#include "nll/collections/linked_list.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

#include <gtest/gtest.h>

class BaseSinglyLinkedListTest : public testing::Test {
 protected:
  nll::SinglyLinkedList<int> list;
};

class PrefilledSinglyLinkedListTest : public testing::Test {
 protected:
  PrefilledSinglyLinkedListTest() {
    for (int i = 1; i < 4; i++) {
      list.PushFront(i);
    }
  }

  nll::SinglyLinkedList<int> list;
};

TEST(SinglyLinkedListTest, CanConstruct) {
  nll::SinglyLinkedList<int> list;
}

TEST_F(BaseSinglyLinkedListTest, CanPushAndPopBack) {
  // Push rvalue
  list.PushBack(1);
  // Push lvalue
  int x = 2;
  list.PushBack(x);
  // Ensure lvalue is copied
  x = 3;
  // Expect values stored successfully
  EXPECT_EQ(list.PopBack(), 2);
  EXPECT_EQ(list.PopBack(), 1);
}

TEST_F(BaseSinglyLinkedListTest, CanPushAndPopFront) {
  // Push rvalue
  list.PushFront(1);
  // Push lvalue
  int x = 2;
  list.PushFront(x);
  // Ensure lvalue is copied
  x = 3;
  // Expect values stored successfully
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 1);
}

TEST_F(BaseSinglyLinkedListTest, CanMixPushAndPopFrontAndBack) {
  list.PushFront(1);
  list.PushBack(2);
  list.PushFront(3);
  list.PushBack(4);
  // Expect values stored successfully
  EXPECT_EQ(list.PopBack(), 4);
  EXPECT_EQ(list.PopFront(), 3);
  EXPECT_EQ(list.PopBack(), 2);
  EXPECT_EQ(list.PopFront(), 1);
}

TEST_F(BaseSinglyLinkedListTest, SizeIsCorrectPushingFront) {
  for (int i = 0; i < 8; i++) {
    list.PushFront(i);
  }
  EXPECT_EQ(list.Size(), 8);
}

TEST_F(BaseSinglyLinkedListTest, SizeIsCorrectPushingBack) {
  for (int i = 0; i < 8; i++) {
    list.PushBack(i);
  }
  EXPECT_EQ(list.Size(), 8);
}

TEST_F(BaseSinglyLinkedListTest, SizeIsCorrectPushingAndPoppingFront) {
  for (int i = 0; i < 8; i++) {
    list.PushFront(i);
  }
  for (int i = 0; i < 8; i++) {
    list.PopFront();
  }
  EXPECT_EQ(list.Size(), 0);
}

TEST_F(BaseSinglyLinkedListTest, SizeIsCorrectPushingAndPoppingBack) {
  for (int i = 0; i < 8; i++) {
    list.PushBack(i);
  }
  for (int i = 0; i < 8; i++) {
    list.PopBack();
  }
  EXPECT_EQ(list.Size(), 0);
}

TEST_F(BaseSinglyLinkedListTest,
       SizeIsCorrectMixedPushingAndPoppingFrontAndBack) {
  for (int i = 0; i < 8; i++) {
    list.PushFront(i);
    list.PushBack(i);
    list.PopBack();
    list.PopFront();
  }
  EXPECT_EQ(list.Size(), 0);
}

TEST_F(BaseSinglyLinkedListTest, CanPopFront) {
  list.PushFront(1);
  list.PushFront(2);
  list.PushFront(3);
  EXPECT_EQ(list.PopFront(), 3);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 1);
}

TEST_F(BaseSinglyLinkedListTest, CanPushBack) {
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 3);
}

TEST_F(BaseSinglyLinkedListTest, ThrowsIfPopWhileEmpty) {
  EXPECT_THROW(list.PopFront(), std::out_of_range);
}

TEST_F(BaseSinglyLinkedListTest, ThrowsIfPeekWhileEmpty) {
  EXPECT_THROW(list.PeekFront(), std::out_of_range);
}

TEST_F(PrefilledSinglyLinkedListTest, IsIterable) {
  auto total = 0;
  for (auto& val : list) {
    total += val;
  }
  EXPECT_EQ(total, 6);
}

TEST_F(PrefilledSinglyLinkedListTest, SearchableWithFindAlgorithm) {
  auto found = std::find(list.begin(), list.end(), 2);
  EXPECT_NE(found, list.end());
  EXPECT_EQ(*found, 2);
}

TEST_F(BaseSinglyLinkedListTest, SearchingEmptyListIsSane) {
  auto found = std::find(list.begin(), list.end(), 2);
  EXPECT_EQ(found, list.end());
}

TEST_F(PrefilledSinglyLinkedListTest, CanIndex) {
  EXPECT_EQ(list[1], 2);
}

TEST(MiscSinglyLinkedListTest, CanAccessValueThroughIterator) {
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

TEST(MiscSinglyLinkedListTest, PushFrontOnlyWithMoveShouldMove) {
  auto list = nll::SinglyLinkedList<std::string>();
  std::string s = "hello world!";
  list.PushFront(s);
  EXPECT_FALSE(s.empty());
  list.PushFront(std::move(s));
  EXPECT_TRUE(s.empty());
}

TEST(MiscSinglyLinkedListTest, PushBackOnlyWithMoveShouldMove) {
  auto list = nll::SinglyLinkedList<std::string>();
  std::string s = "hello world!";
  list.PushBack(s);
  EXPECT_FALSE(s.empty());
  list.PushBack(std::move(s));
  EXPECT_TRUE(s.empty());
}

TEST_F(PrefilledSinglyLinkedListTest, RemovingHeadValueSucceeds) {
  list.Remove(3);
  EXPECT_EQ(list.PeekFront(), 2);
}

TEST_F(PrefilledSinglyLinkedListTest, RemovingMiddleValueSucceeds) {
  list.Remove(2);
  EXPECT_EQ(list.Size(), 2);
}

TEST_F(PrefilledSinglyLinkedListTest, RemovingTailValueSucceeds) {
  list.Remove(1);
  EXPECT_EQ(list.Size(), 2);
}

TEST_F(PrefilledSinglyLinkedListTest, SizeIsCorrectAfterClear) {
  list.Clear();
  EXPECT_EQ(list.Size(), 0);
}

TEST_F(PrefilledSinglyLinkedListTest, CantPeekOrPopAfterClear) {
  list.Clear();
  EXPECT_THROW(list.PeekFront(), std::out_of_range);
  EXPECT_THROW(list.PopFront(), std::out_of_range);
}

TEST(MiscSinglyLinkedListTest, WorksWithFreakyTypes) {
  auto list = nll::SinglyLinkedList<std::pair<std::string, std::string>>();
  list.PushBack(std::make_pair("Hello", "World"));
}

TEST_F(BaseSinglyLinkedListTest, ReverseSucceeds) {
  for (int i = 0; i < 5; i++) {
    list.PushBack(i);
  }
  list.Reverse();
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(list[i], 5 - 1 - i);
  }
}