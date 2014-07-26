#include <catch.hpp>

#include "math_vector2.hpp"

using aff::math::Vector2i;
using aff::math::Vector2f;
using aff::math::Vector2d;

TEST_CASE("Vectors can perform math operations") {
  SECTION("Addition of vectors") {
    Vector2i a(1, -2);
    Vector2i b(2, 1);
    Vector2i sum = a + b;
    REQUIRE(sum.x_ == 3);
    REQUIRE(sum.y_ == -1);

    // Default constructor does zero initialization
    Vector2i zero;
    Vector2i sum_with_zero = a + zero;
    REQUIRE(sum_with_zero.x_ == a.x_);
    REQUIRE(sum_with_zero.y_ == a.y_);
  }

  SECTION("Subtraction of vectors") {
    Vector2i a(0, -1);
    Vector2i b(3, 0);
    Vector2i sub = a - b;
    REQUIRE(sub.x_ == -3);
    REQUIRE(sub.y_ == -1);

    Vector2i zero;
    Vector2i sub_with_zero = a - zero;
    REQUIRE(sub_with_zero.x_ == a.x_);
    REQUIRE(sub_with_zero.y_ == a.y_);
  }
}

TEST_CASE("Immutability of 2 dimensional vector") {
  SECTION("Vector of ints") {
    Vector2i a(1, 2);
    Vector2i b(2, 1);

    a + b;
    a - b;
    REQUIRE(a.x_ == 1);
    REQUIRE(a.y_ == 2);
    REQUIRE(b.x_ == 2);
    REQUIRE(b.y_ == 1);
  }
}