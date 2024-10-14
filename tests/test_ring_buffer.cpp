#include "nll/collections/ring_buffer.hpp"

#include <stdexcept>

#include <gtest/gtest.h>

#include <nll/macros.hpp>

TEST(RingBufferTest, EmptyBufferIsEmpty) {
  nll::RingBuffer<int, 16> queue;
  EXPECT_TRUE(queue.Empty());
}

TEST(RingBufferTest, PeekOrPopFromEmptyBufferThrows) {
  nll::RingBuffer<int, 16> queue;
  EXPECT_THROW(queue.Peek(), std::runtime_error);
  EXPECT_THROW(queue.Pop(), std::runtime_error);
}

TEST(RingBufferTest, CanPushElement) {
  nll::RingBuffer<int, 16> queue;
  queue.Push(1);
  queue.Push(2);
  queue.Push(3);
  EXPECT_EQ(queue.Pop(), 1);
  EXPECT_EQ(queue.Pop(), 2);
  EXPECT_EQ(queue.Pop(), 3);
}

TEST(RingBufferTest, IsCircular) {
  nll::RingBuffer<int, 16> queue;
  // Queue size 16, so after pushing 16 elements, the 17th should overwrite "0"
  // Thus queue.Pop() should return the second oldest element which is 2
  for (int i = 0; i < 17; i++) {
    queue.Push(i);
  }

  EXPECT_EQ(queue.Pop(), 2);
  EXPECT_EQ(queue.Pop(), 3);
  EXPECT_EQ(queue.Pop(), 4);
}

/*
Tests that reads which span the wraparound are successful
*/
TEST(RingBufferTest, CanReadAcrossWraparound) {
  nll::RingBuffer<int, 16> queue;
  for (int i = 0; i < (16 - 3); i++) {
    queue.Push(i);
    queue.Pop();
  }

  EXPECT_TRUE(queue.Empty());

  for (int i = 0; i < 6; i++) {
    queue.Push(i);
  }

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(queue.Pop(), i);
  }
}

TEST(RingBufferTest, CanClear) {
  nll::RingBuffer<int, 16> queue;
  for (int i = 0; i < 16; i++) {
    queue.Push(i);
  }
  for (int i = 0; i < 8; i++) {
    queue.Pop();
  }

  queue.Clear();

  EXPECT_EQ(queue.Size(), 0);
}