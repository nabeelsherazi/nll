#pragma once

#include <stdexcept>
#include <vector>

namespace nll {

class BinaryTreeNode {
 public:
  explicit BinaryTreeNode(int value) : value_(value) {};

  int value_;
  BinaryTreeNode* left_ = nullptr;
  BinaryTreeNode* right_ = nullptr;
};

class BinaryTree {
 public:
  ~BinaryTree() { delete root_; }

  void Insert(int value) {
    if (!root_) {
      auto newNode = new BinaryTreeNode(value);
      root_ = newNode;
    }
    // To be filled in ...
  }

  int GetRoot() {
    if (!root_) {
      throw std::runtime_error("tree has no nodes!");
    }
    return root_->value();
  }

 private:
  BinaryTreeNode* root_ = nullptr;
};

}  // namespace nll