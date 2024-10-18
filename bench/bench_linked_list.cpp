#include "nll/collections/linked_list.hpp"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

static void BM_LinkedListFind(benchmark::State& state) {
  // Setup
  nll::SinglyLinkedList<int> list{};
  // Generate list of numbers from 0..n in random order
  constexpr int kNumElements = 1024;
  std::vector<int> inputElements(kNumElements);
  std::iota(inputElements.begin(), inputElements.end(), 0);
  auto rng = std::default_random_engine{};
  std::shuffle(inputElements.begin(), inputElements.end(), rng);
  // Fill linked list
  for (auto i : inputElements) {
    list.PushBack(i);
  }
  for (auto _ : state) {
    // This code gets timed
    for (int i = 0; i < kNumElements; i++) {
      benchmark::DoNotOptimize(std::find(list.cbegin(), list.cend(), i));
    }
  }
}

static void BM_LinkedListRandomFillBack(benchmark::State& state) {
  // Setup
  nll::SinglyLinkedList<int> list{};

  // Generate list of numbers from 0..n in random order
  constexpr int kNumElements = 1024;
  std::vector<int> inputElements(kNumElements);
  std::iota(inputElements.begin(), inputElements.end(), 0);
  auto rng = std::default_random_engine{};
  std::shuffle(inputElements.begin(), inputElements.end(), rng);

  for (auto _ : state) {
    // This code gets timed
    for (auto i : inputElements) {
      list.PushBack(i);
    }
  }
}

static void BM_LinkedListRandomFillFront(benchmark::State& state) {
  // Setup
  nll::SinglyLinkedList<int> list{};

  // Generate list of numbers from 0..n in random order
  constexpr int kNumElements = 1024;
  std::vector<int> inputElements(kNumElements);
  std::iota(inputElements.begin(), inputElements.end(), 0);
  auto rng = std::default_random_engine{};
  std::shuffle(inputElements.begin(), inputElements.end(), rng);

  for (auto _ : state) {
    // This code gets timed
    for (auto i : inputElements) {
      list.PushFront(i);
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_LinkedListFind)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_LinkedListRandomFillBack)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_LinkedListRandomFillFront)->Unit(benchmark::kMillisecond);
// Run the benchmark
BENCHMARK_MAIN();