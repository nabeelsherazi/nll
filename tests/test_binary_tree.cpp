#include "nll/collections/binary_tree.hpp"

#include <memory>
#include <stdexcept>

#include <gtest/gtest.h>

#include <nll/macros.hpp>

TEST(BinaryTreeTest, Creation) {
  auto root = std::make_unique<nll::BinaryTreeNode>(1);
  root->left = std::make_unique<nll::BinaryTreeNode>(2);
  root->right = std::make_unique<nll::BinaryTreeNode>(3);
  root->left->left = std::make_unique<nll::BinaryTreeNode>(4);
  root->left->right = std::make_unique<nll::BinaryTreeNode>(5);
  EXPECT_EQ(root->value, 1);
  EXPECT_EQ(root->left->value, 2);
  EXPECT_EQ(root->left->left->value, 4);
  EXPECT_EQ(root->left->right->value, 5);
  EXPECT_EQ(root->right->value, 3);
}
