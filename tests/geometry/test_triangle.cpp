#include "nll/geometry/triangles.hpp"

#include <gtest/gtest.h>

#include "nll/geometry/point.hpp"

TEST(TriangleTest, CanCalculateArea) {
    auto a = nll::geometry::Point2d(0.0, 0.0);
    auto b = nll::geometry::Point2d(0.0, 1.0);
    auto c = nll::geometry::Point2d(1.0, 0.0);
    auto area = nll::geometry::areaOfTriangle(a, b, c);
    ASSERT_FLOAT_EQ(area, 0.5);
}

