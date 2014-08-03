#include <catch.hpp>

#include "math_vector2.hpp"
#include "math_util.hpp"

using aff::math::Vector2i;
using aff::math::Vector2f;
using aff::math::AlmostEqual;

TEST_CASE("2D vectors can be initialize") {
  SECTION("Zero initialization") {
    Vector2i zero_i;
    REQUIRE(zero_i.x == 0);
    REQUIRE(zero_i.y == 0);
    Vector2f zero_f;
    REQUIRE(AlmostEqual(zero_f.x, 0.0f));
    REQUIRE(AlmostEqual(zero_f.y, 0.0f));
  }

  SECTION("Full initialization") {
    Vector2i full_i(-2, 0);
    REQUIRE(full_i.x == -2);
    REQUIRE(full_i.y == 0);
    Vector2f full_f(2.3f, -0.03f);
    REQUIRE(AlmostEqual(full_f.x, 2.3f));
    REQUIRE(AlmostEqual(full_f.y, -0.03f));
  }
}

TEST_CASE("2D Vectors can perform math operations") {
  SECTION("Reverse vectors") {
    Vector2i reverse_zero = -Vector2i::Zero;
    REQUIRE(reverse_zero.x == 0);
    REQUIRE(reverse_zero.y == 0);
    Vector2f reverse_full = -Vector2f(3.1f, -0.9f);
    REQUIRE(AlmostEqual(reverse_full.x, -3.1f));
    REQUIRE(AlmostEqual(reverse_full.y, 0.9f));
    Vector2f double_reverse = -(-Vector2f::Ones);
    REQUIRE(double_reverse == Vector2f::Ones);
  }

  SECTION("Addition of vectors") {
    Vector2i a(1, -2);
    Vector2i b(2, 1);
    Vector2i result(3, -1);
    REQUIRE((a + b) == result);
    REQUIRE((b + a) == result);
    REQUIRE((a + Vector2i::Zero) == a);
    REQUIRE((Vector2i::Zero + a) == a);
    REQUIRE((a + Vector2i::Ones) == Vector2i(2, -1));
  }

  SECTION("Subtraction of vectors") {
    Vector2i a(0, -1);
    Vector2i b(3, 0);
    Vector2i result(-3, -1);
    REQUIRE((a - b) == result);
    REQUIRE((b - a) != result);
    REQUIRE((a - Vector2i::Zero) == a);
    REQUIRE((Vector2i::Zero - a) == -a);
    REQUIRE((Vector2i::Ones - b) == Vector2i(-2, 1));
  }

  SECTION("Multiplication of vector and scalar") {
    Vector2f a(2, -3);
    float alfa = 3;
    Vector2f result(6, -9);
    REQUIRE((a * alfa) == result);
    REQUIRE((alfa * a) == result);
    REQUIRE((0.0 * a) == Vector2f::Zero);
    REQUIRE((1 * a) == a);
    Vector2i b(-0, 2);
    REQUIRE((0.0f * b) == Vector2i::Zero);
    REQUIRE((alfa * Vector2i::Zero) == Vector2i::Zero);
    REQUIRE((alfa * Vector2i::Ones) == Vector2i(3, 3));
  }

  SECTION("Magnitude of vector") {
    float ones_magnitude = Vector2f::Ones.Magnitude();
    REQUIRE(AlmostEqual(ones_magnitude, 1.41421f, 0.0001f));
    float zero_magnitude = Vector2i::Zero.Magnitude();
    REQUIRE(AlmostEqual(zero_magnitude, 0.0f));
  }

  SECTION("Vector normalization") {
    auto ones_normalized = Vector2f::Ones.Normalize();
    REQUIRE(AlmostEqual(ones_normalized.x, 0.707109f, 0.0001f));
    REQUIRE(AlmostEqual(ones_normalized.y, 0.707109f, 0.0001f));
    float ones_magnitude = ones_normalized.Magnitude();
    REQUIRE(AlmostEqual(ones_magnitude, 1.0f));
    auto zero_normalized = Vector2i::Zero.Normalize();
    float zero_magnitude = zero_normalized.Magnitude();
    REQUIRE(AlmostEqual(zero_magnitude, 0.0f));
  }

  SECTION("Vectors (in)equality") {
    Vector2f a(2.3f, -1.2f + 2.0f);
    Vector2f b(2.3f, 0.8f);
    Vector2f c(1.333f, 2.3f);
    REQUIRE(a == b);
    REQUIRE(!(a != b));
    REQUIRE(a != c);
    REQUIRE(b != c);
    REQUIRE(c == c);
  }
}
