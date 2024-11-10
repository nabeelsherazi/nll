#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "nll/collections/linked_list.hpp"

namespace nll {

template <class TKey, class TValue>
class Hashmap {
 private:
  std::vector<SinglyLinkedList<std::pair<TKey, TValue>>> table;
  std::size_t num_buckets = 1;
  std::size_t size = 0;
  const double max_load_factor = 0.75;
  std::hash<TKey> hasher{};

  /// @brief Resizes the hashmap to a new number of buckets
  /// @param new_num_buckets
  void Resize(std::size_t new_num_buckets) {
    std::vector<SinglyLinkedList<std::pair<TKey, TValue>>> new_table(
        new_num_buckets);
    for (auto& list : table) {
      for (auto& pair : list) {
        auto hash = hasher(pair.first);
        auto index = hash % new_num_buckets;
        new_table[index].PushBack(pair);
      }
    }
    table = std::move(new_table);
    num_buckets = new_num_buckets;
  }

  /// @brief Resizes the hashmap if the load factor is exceeded
  /// @return true if the hashmap was resized
  bool ResizeIfNeeded() {
    if (size >= num_buckets * max_load_factor) {
      Resize(num_buckets * 2);
      return true;
    }
    return false;
  }

  inline std::size_t GetBucketIndex(TKey key) {
    auto hash = hasher(key);
    return hash % num_buckets;
  }

 public:
  /// @brief Default constructor
  Hashmap() { table.resize(this->num_buckets); }

  /// @brief Constructor with initial number of buckets
  /// @param num_buckets initial number of buckets
  explicit Hashmap(std::size_t num_buckets) : num_buckets(num_buckets) {
    table.resize(this->num_buckets);
  }

  /// @brief Get the current size of the hashmap
  /// @return the number of key-value pairs in the hashmap
  std::size_t Size() const { return size; }

  /// @brief Returns whether the hashmap is empty or not
  bool Empty() const { return Size() == 0; }

  /// @brief Clears all key-value pairs from the hashmap
  void Clear() {
    for (auto& list : table) {
      list.Clear();
    }
    size = 0;
  }

  /// @brief Inserts a key-value pair into the hashmap
  /// @param key the key to insert
  /// @param value the value to insert
  void Insert(TKey key, TValue value) {
    auto hash = hasher(key);
    auto index = hash % num_buckets;
    for (auto& pair : table[index]) {
      if (pair.first == key) {
        pair.second = value;
        return;
      }
    }
    table[index].PushBack(std::make_pair(key, value));
    size++;
    ResizeIfNeeded();
  }

  /// @brief Removes a key-value pair from the hashmap
  /// @param key the key to remove
  /// @note TODO: Fix this stupid implementation
  void Remove(TKey key) {
    auto index = GetBucketIndex(key);
    table[index].Remove(std::make_pair(key, this->Get(key)));
  }

  /// @brief Checks if a key exists in the hashmap
  /// @param key the key to search for
  /// @return true if the key exists
  bool Contains(TKey key) {
    auto index = GetBucketIndex(key);
    for (auto& pair : table[index]) {
      if (pair.first == key) {
        return true;
      }
    }
    return false;
  }

  /// @brief Gets the value associated with a key
  /// @param key the key to search for
  /// @return the value associated with the key
  /// @throws std::out_of_range if the key is not found
  TValue& Get(TKey key) {
    auto index = GetBucketIndex(key);
    for (auto& pair : table[index]) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    throw std::out_of_range("key not found!");
  }

  /// @brief Overloads the index operator to set a value
  /// @param key the key to set
  /// @return the value associated with the key
  /// @note if the key does not exist, it will be default created
  TValue& operator[](TKey key) {
    // Find key and return if it exists
    auto index = GetBucketIndex(key);
    for (auto& pair : table[index]) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    // Otherwise, default create a new pair for this key
    table[index].PushBack(std::make_pair(key, TValue()));
    size++;
    // If adding a new element causes us to resize, recompute the index
    bool did_resize = ResizeIfNeeded();
    if (did_resize) {
      index = GetBucketIndex(key);
    }
    return table[index].PeekBack().second;
  }
};

}  // namespace nll