#include "nll/graph/binary_tree.hpp"

#include <gtest/gtest.h>

TEST(BinaryTreeTest, Basic) {
  auto node = new nll::binary_tree::Node<int>(1);
  node->left = new nll::binary_tree::Node<int>(2);
  node->right = new nll::binary_tree::Node<int>(3);

  ASSERT_TRUE(nll::binary_tree::is_balanced(node));
  delete node->right;
  delete node->left;
  delete node;
}