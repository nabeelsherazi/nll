#include "nll/geometry/point.hpp"

#include <gtest/gtest.h>

// Tests for Point2d

TEST(Point2dCreationTest, CanCreate) {
  auto point = nll::geometry::Point2d(2.0, 3.0);
  ASSERT_FLOAT_EQ(point.x, 2.0);
  ASSERT_FLOAT_EQ(point.y, 3.0);
}

TEST(Point2dOperationsTest, CanAddScalar) {
  auto point = nll::geometry::Point2d(2.0, 3.0);
  point = point + 2.0;
  ASSERT_FLOAT_EQ(point.x, 4.0);
  ASSERT_FLOAT_EQ(point.y, 5.0);
}

TEST(Point2dOperationsTest, CanSubtractScalar) {
  auto point = nll::geometry::Point2d(2.0, 3.0);
  point = point - 2.0;
  ASSERT_FLOAT_EQ(point.x, 0.0);
  ASSERT_FLOAT_EQ(point.y, 1.0);
}

TEST(Point2dOperationsTest, CanDivideScalar) {
  auto point = nll::geometry::Point2d(2.0, 3.0);
  point = point + 2.0;
  ASSERT_FLOAT_EQ(point.x, 4.0);
  ASSERT_FLOAT_EQ(point.y, 5.0);
}
TEST(Point2dOperationsTest, CanMultiplyScalar) {
    auto point = nll::geometry::Point2d(2.0, 3.0);
    point = point * 2.0;
    ASSERT_FLOAT_EQ(point.x, 4.0);
    ASSERT_FLOAT_EQ(point.y, 6.0);
}

TEST(Point2dOperationsTest, CanAddPoint) {
    auto point1 = nll::geometry::Point2d(2.0, 3.0);
    auto point2 = nll::geometry::Point2d(1.0, 1.0);
    auto result = point1 + point2;
    ASSERT_FLOAT_EQ(result.x, 3.0);
    ASSERT_FLOAT_EQ(result.y, 4.0);
}

TEST(Point2dOperationsTest, CanSubtractPoint) {
    auto point1 = nll::geometry::Point2d(2.0, 3.0);
    auto point2 = nll::geometry::Point2d(1.0, 1.0);
    auto result = point1 - point2;
    ASSERT_FLOAT_EQ(result.x, 1.0);
    ASSERT_FLOAT_EQ(result.y, 2.0);
}

TEST(Point2dOperationsTest, CanGetNorm) {
    auto point = nll::geometry::Point2d(3.0, 4.0);
    auto norm = point.norm();
    ASSERT_FLOAT_EQ(norm, 5.0);
}

// Tests for Point2f

TEST(Point2fCreationTest, CanCreate) {
  auto point = nll::geometry::Point2f(2.0F, 3.0F);
  ASSERT_FLOAT_EQ(point.x, 2.0F);
  ASSERT_FLOAT_EQ(point.y, 3.0F);
}

TEST(Point2fOperationsTest, CanAddScalar) {
    auto point = nll::geometry::Point2f(2.0F, 3.0F);
    point = point + 2.0F;
    ASSERT_FLOAT_EQ(point.x, 4.0F);
    ASSERT_FLOAT_EQ(point.y, 5.0F);
}

TEST(Point2fOperationsTest, CanSubtractScalar) {
    auto point = nll::geometry::Point2f(2.0F, 3.0F);
    point = point - 2.0F;
    ASSERT_FLOAT_EQ(point.x, 0.0F);
    ASSERT_FLOAT_EQ(point.y, 1.0F);
}

TEST(Point2fOperationsTest, CanDivideScalar) {
    auto point = nll::geometry::Point2f(2.0F, 3.0F);
    point = point / 2.0F;
    ASSERT_FLOAT_EQ(point.x, 1.0F);
    ASSERT_FLOAT_EQ(point.y, 1.5F);
}

TEST(Point2fOperationsTest, CanMultiplyScalar) {
    auto point = nll::geometry::Point2f(2.0F, 3.0F);
    point = point * 2.0F;
    ASSERT_FLOAT_EQ(point.x, 4.0F);
    ASSERT_FLOAT_EQ(point.y, 6.0F);
}

TEST(Point2fOperationsTest, CanAddPoint) {
    auto point1 = nll::geometry::Point2f(2.0F, 3.0F);
    auto point2 = nll::geometry::Point2f(1.0F, 1.0F);
    auto result = point1 + point2;
    ASSERT_FLOAT_EQ(result.x, 3.0F);
    ASSERT_FLOAT_EQ(result.y, 4.0F);
}

TEST(Point2fOperationsTest, CanSubtractPoint) {
    auto point1 = nll::geometry::Point2f(2.0F, 3.0F);
    auto point2 = nll::geometry::Point2f(1.0F, 1.0F);
    auto result = point1 - point2;
    ASSERT_FLOAT_EQ(result.x, 1.0F);
    ASSERT_FLOAT_EQ(result.y, 2.0F);
}

TEST(Point2fOperationsTest, CanGetNorm) {
    auto point = nll::geometry::Point2f(3.0F, 4.0F);
    auto norm = point.norm();
    ASSERT_FLOAT_EQ(norm, 5.0F);
}

// Tests for Point2i

TEST(Point2iCreationTest, CanCreate) {
  auto point = nll::geometry::Point2i(2, 3);
  ASSERT_FLOAT_EQ(point.x, 2);
  ASSERT_FLOAT_EQ(point.y, 3);
}
TEST(Point2iOperationsTest, CanAddScalar) {
    auto point = nll::geometry::Point2i(2, 3);
    point = point + 2;
    ASSERT_EQ(point.x, 4);
    ASSERT_EQ(point.y, 5);
}

TEST(Point2iOperationsTest, CanSubtractScalar) {
    auto point = nll::geometry::Point2i(2, 3);
    point = point - 2;
    ASSERT_EQ(point.x, 0);
    ASSERT_EQ(point.y, 1);
}

TEST(Point2iOperationsTest, CanDivideScalar) {
    auto point = nll::geometry::Point2i(4, 6);
    point = point / 2;
    ASSERT_EQ(point.x, 2);
    ASSERT_EQ(point.y, 3);
}

TEST(Point2iOperationsTest, DividingScalarCausesIntegerDivision) {
    auto point = nll::geometry::Point2i(5, 3);
    point = point / 2;
    ASSERT_EQ(point.x, 2);
    ASSERT_EQ(point.y, 1);
}

TEST(Point2iOperationsTest, CanMultiplyScalar) {
    auto point = nll::geometry::Point2i(2, 3);
    point = point * 2;
    ASSERT_EQ(point.x, 4);
    ASSERT_EQ(point.y, 6);
}

TEST(Point2iOperationsTest, CanAddPoint) {
    auto point1 = nll::geometry::Point2i(2, 3);
    auto point2 = nll::geometry::Point2i(1, 1);
    auto result = point1 + point2;
    ASSERT_EQ(result.x, 3);
    ASSERT_EQ(result.y, 4);
}

TEST(Point2iOperationsTest, CanSubtractPoint) {
    auto point1 = nll::geometry::Point2i(2, 3);
    auto point2 = nll::geometry::Point2i(1, 1);
    auto result = point1 - point2;
    ASSERT_EQ(result.x, 1);
    ASSERT_EQ(result.y, 2);
}

TEST(Point2iOperationsTest, CanGetNorm) {
    auto point = nll::geometry::Point2i(3, 4);
    auto norm = point.norm();
    ASSERT_FLOAT_EQ(norm, 5);
}
