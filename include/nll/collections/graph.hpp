#pragma once

#include <stdexcept>
#include <vector>

namespace nll {

template <class T>
class GraphNode {
 public:
  explicit GraphNode(T value) : value_(value), adjacent_nodes_() {};

  void AddAdjacentNode(GraphNode* node) { adjacent_nodes_.push_back(node); }

  T value() { return value_; }

 protected:
  std::vector<GraphNode*> adjacent_nodes_;
  T value_;
};

template <class T>
class BinaryTreeNode : public GraphNode<T> {
 public:
  using GraphNode<T>::value;

  explicit BinaryTreeNode(T value) : GraphNode<T>(value) {
    this->adjacent_nodes_.resize(2, nullptr);
  };

  T GetLeft() { return this->adjacent_nodes_[0]; }

  T GetRight() { return this->adjacent_nodes_[1]; }

  void SetLeft(BinaryTreeNode* node) { this->adjacent_nodes_[0] = node; };

  void SetRight(BinaryTreeNode* node) { this->adjacent_nodes_[1] = node; };
};

template <class T>
class BinaryTree {
 public:
  ~BinaryTree() { delete root_; }

  void Insert(T value) {
    if (!root_) {
      auto newNode = new BinaryTreeNode<T>(value);
      root_ = newNode;
    }
    // To be filled in ...
  }

  T GetRoot() {
    if (!root_) {
      throw std::runtime_error("tree has no nodes!");
    }
    return root_->value();
  }

 private:
  GraphNode<T>* CreateTreeNode(T value) {
    auto newNode = new GraphNode<T>(value);
    newNode->addAdjacentNode(nullptr);
    newNode->addAdjacentNode(nullptr);
  }
  GraphNode<T>* root_ = nullptr;
};

}  // namespace nll