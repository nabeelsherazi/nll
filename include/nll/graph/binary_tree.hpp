#pragma once

namespace nll {
namespace binary_tree {

template<class T>
struct Node {
    T value;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;

    explicit Node(T val) : value(val) {};
};


template <class T>
bool is_balanced(Node<T>* root) {
    return true;
};

}
}