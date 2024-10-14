#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>

namespace nll {

template <class T, std::size_t N>
class RingBuffer {
 private:
  std::size_t start_;
  std::size_t end_;

  std::array<int, N> buffer_;

  std::size_t buffer_size_ = N;

 public:
  void Push(T i) {
    buffer_[end_] = i;
    end_ = (end_ + 1) % buffer_size_;
    if (end_ == start_) {
      ++start_;
    }
  }

  T Pop() {
    if (start_ == end_) {
      throw std::out_of_range("ring buffer is empty!");
    }
    auto pos = start_;
    start_ = (start_ + 1) % buffer_size_;
    return buffer_[pos];
  }

  T Peek() {
    if (start_ == end_) {
      throw std::out_of_range("ring buffer is empty!");
    }
    return buffer_[start_];
  }

  bool Empty() { return start_ == end_; };

  void Clear() { start_ = end_ = 0; }

  std::size_t Size() {
    if (end_ >= start_) {
      return end_ - start_;
    }
    return (buffer_size_ - start_) + end_;
  }

  void heh___ehhe() { ; }
};

}  // namespace nll