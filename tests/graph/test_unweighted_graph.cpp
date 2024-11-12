#include "nll/graph/unweighted_graph.hpp"

#include <gtest/gtest.h>

// Fixture for a simple graph
class DiamondGraphTest : public ::testing::Test {
 protected:
  void SetUp() override {
    auto node1 = graph.AddNode(1);
    auto node2 = graph.AddNode(2);
    auto node3 = graph.AddNode(3);
    auto node4 = graph.AddNode(4);

    // 1 -> {2, 3}
    node1->AddNeighbor(node2);
    node1->AddNeighbor(node3);
    // {2, 3} -> 4
    node2->AddNeighbor(node4);
    node3->AddNeighbor(node4);
    // 2 -> 3
    node2->AddNeighbor(node3);
  }

  nll::graph::UnweightedGraph<int> graph;
};

TEST_F(DiamondGraphTest, Basic) {
  // 1 -> {2, 3}
  ASSERT_EQ(graph.nodes[0]->neighbors.size(), 2);
  // {2, 3} -> 4
  ASSERT_EQ(graph.nodes[1]->neighbors.size(), 1);
  ASSERT_EQ(graph.nodes[2]->neighbors.size(), 1);
  // 2 -> 3
  ASSERT_EQ(graph.nodes[1]->neighbors[0]->neighbors.size(), 1);
}