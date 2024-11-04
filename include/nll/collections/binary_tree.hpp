#pragma once

#include <memory>
#include <stdexcept>

#include <fmt/core.h>

namespace nll {

class BinaryTreeNode {
 public:
  explicit BinaryTreeNode(int value) : value(value) {};

  int value;
  std::unique_ptr<BinaryTreeNode> left = nullptr;
  std::unique_ptr<BinaryTreeNode> right = nullptr;
};

}  // namespace nll