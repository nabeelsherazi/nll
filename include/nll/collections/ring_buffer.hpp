#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>

namespace nll {

template <class T, std::size_t N>
class RingBuffer {
 private:
  std::size_t start;
  std::size_t end;

  std::array<int, N> buffer;

  std::size_t buffer_size = N;

 public:
  void Push(T i) {
    this->buffer[this->end] = i;
    this->end = (this->end + 1) % buffer_size;
    if (this->end == this->start) {
      ++this->start;
    }
  }

  T Pop() {
    if (this->start == this->end) {
      throw std::runtime_error("ring buffer is empty!");
    }
    auto pos = this->start;
    this->start = (this->start + 1) % this->buffer_size;
    return this->buffer[pos];
  }

  T Peek() {
    if (this->start == this->end) {
      throw std::runtime_error("ring buffer is empty!");
    }
    return this->buffer[this->start];
  }

  bool Empty() { return this->start == this->end; };

  void Clear() { this->start = this->end = 0; }

  std::size_t Size() {
    if (this->end >= this->start) {
      return this->end - this->start;
    } else {
      return (this->buffer_size - this->start) + this->end;
    }
  }
};

}  // namespace nll