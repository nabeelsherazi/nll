#pragma once

#include <memory>
#include <vector>

namespace nll {
namespace graph {

template <class T>
class UnweightedGraphNode {
 public:
  T value;
  std::vector<UnweightedGraphNode<T>*> neighbors;

  explicit UnweightedGraphNode(T val) : value(val) {};

  void AddNeighbor(UnweightedGraphNode<T>* neighbor) {
    neighbors.push_back(neighbor);
    neighbor->neighbors.push_back(this);
  }
};

template <class T>
class UnweightedGraph {
 public:
  std::vector<std::unique_ptr<UnweightedGraphNode<T>>> nodes;

  UnweightedGraphNode<T>* AddNode(T value) {
    nodes.push_back(std::make_unique<UnweightedGraphNode<T>>(value));
    return nodes.back().get();
  }
};

}  // namespace graph
}  // namespace nll