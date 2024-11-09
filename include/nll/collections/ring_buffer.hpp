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
    buffer[end] = i;
    end = (end + 1) % buffer_size;
    if (end == start) {
      ++start;
    }
  }

  T Pop() {
    if (start == end) {
      throw std::out_of_range("ring buffer is empty!");
    }
    auto pos = start;
    start = (start + 1) % buffer_size;
    return buffer[pos];
  }

  T Peek() {
    if (start == end) {
      throw std::out_of_range("ring buffer is empty!");
    }
    return buffer[start];
  }

  bool Empty() { return start == end; };

  void Clear() { start = end = 0; }

  std::size_t Size() {
    if (end >= start) {
      return end - start;
    }
    return (buffer_size - start) + end;
  }
};

}  // namespace nll