#pragma once

#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "nll/collections/linked_list.hpp"

namespace nll {

class Hashmap {
private:
    std::vector<SinglyLinkedList<std::pair<std::string, std::string>>> table;
    std::size_t num_buckets = 16;
    std::hash<std::string> hasher {};

public:
    Hashmap() {
        table.resize(this->num_buckets);
    }

    void Insert(std::string key, std::string value) {
        auto hash = hasher(key);
        auto index = hash % num_buckets;
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].PushBack(std::make_pair(key, value));
    }

    std::string& Get(std::string key) {
        auto hash = hasher(key);
        auto index = hash % num_buckets;
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::out_of_range("key not found!");
    }

    std::string& operator[](std::string key) {
        auto hash = hasher(key);
        auto index = hash % num_buckets;
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        table[index].PushBack(std::make_pair(key, std::string()));
        return table[index].PeekBack().second;
    }
};

}