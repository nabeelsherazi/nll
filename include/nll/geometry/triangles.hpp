#pragma once

#include <cmath>

#include "nll/geometry/point.hpp"

namespace nll {
namespace geometry {

template <class T>
T areaOfTriangle(Point2<T> a, Point2<T> b, Point2<T> c) {
  return std::abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) /
                  2);
}
}  // namespace geometry
}  // namespace nll