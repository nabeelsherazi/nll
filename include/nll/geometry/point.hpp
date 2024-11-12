#pragma once

#include <cmath>

namespace nll {
namespace geometry {

template <class T>
class Point2 {
 public:
  T x;
  T y;

  Point2(T x, T y) : x(x), y(y) {};

  // Scalar operations

  Point2<T> operator+(T addend) { return Point2<T>(x + addend, y + addend); }

  Point2<T> operator-(T subtrahend) {
    return Point2<T>(x - subtrahend, y - subtrahend);
  }

  Point2<T> operator*(T multiplier) {
    return Point2<T>(x * multiplier, y * multiplier);
  }

  Point2<T> operator/(T divisor) { return Point2<T>(x / divisor, y / divisor); }

  // Point operations

  Point2<T> operator-(Point2<T>& rhs) {
    return Point2<T>(x - rhs.x, y - rhs.y);
  }

  Point2<T> operator+(Point2<T>& rhs) {
    return Point2<T>(x + rhs.x, y + rhs.y);
  }

  // Member functions

  T norm() const { return static_cast<T>(std::sqrt(x * x + y * y)); }
};

using Point2f = Point2<float>;
using Point2d = Point2<double>;
using Point2i = Point2<int>;

template <class T>
class Point3 {
 public:
  T x;
  T y;
  T z;

  Point3(T x, T y, T z) : x(x), y(y), z(z) {};

  // Scalar operations

  Point3<T> operator+(T addend) {
    return Point3<T>(x + addend, y + addend, z + addend);
  }

  Point3<T> operator-(T subtrahend) {
    return Point3<T>(x - subtrahend, y - subtrahend, z - subtrahend);
  }

  Point3<T> operator*(T multiplier) {
    return Point3<T>(x * multiplier, y * multiplier, z * multiplier);
  }

  Point3<T> operator/(T divisor) {
    return Point3<T>(x / divisor, y / divisor, z / divisor);
  }

  // Point operations

  Point3<T> operator-(Point3<T>& rhs) {
    return Point3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  Point3<T> operator+(Point3<T>& rhs) {
    return Point3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  // Member functions

  T norm() const { return static_cast<T>(std::sqrt(x * x + y * y + z * z)); }
};

using Point3f = Point3<float>;
using Point3d = Point3<double>;
using Point3i = Point3<int>;

}  // namespace geometry
}  // namespace nll