#pragma once

#include "nll/collections/hashmap.hpp"

namespace nll {
    
class Set {
private:
    Hashmap hashmap;
    
public:
    void Add(std::string key) {
        hashmap[key] = "exists";
    }

    bool Contains(std::string key) {
        return hashmap[key] == "exists";
    }

};

}