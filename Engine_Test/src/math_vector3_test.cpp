#include <catch.hpp>

#include "math_vector3.hpp"
#include "math_util.hpp"

using aff::math::Vector3i;
using aff::math::Vector3f;
using aff::math::AlmostEqual;

TEST_CASE("3D vectors can be initialize") {
  SECTION("Zero initialization") {
    Vector3i zero_i;
    REQUIRE(zero_i.x == 0);
    REQUIRE(zero_i.y == 0);
    REQUIRE(zero_i.z == 0);
    Vector3f zero_f;
    REQUIRE(AlmostEqual(zero_f.x, 0.0f));
    REQUIRE(AlmostEqual(zero_f.y, 0.0f));
    REQUIRE(AlmostEqual(zero_f.z, 0.0f));
  }

  SECTION("Full initialization") {
    Vector3i full_i(1, 0, -2);
    REQUIRE(full_i.x == 1);
    REQUIRE(full_i.y == 0);
    REQUIRE(full_i.z == -2);
    Vector3f full_f(2.3f, 0.0f, -1.0f);
    REQUIRE(AlmostEqual(full_f.x, 2.3f));
    REQUIRE(AlmostEqual(full_f.y, 0.0f));
    REQUIRE(AlmostEqual(full_f.z, -1.0f));
  }
}

TEST_CASE("3D Vectors can perform math operations") {
  SECTION("Reverse vectors") {
    Vector3i reverse_zero = -Vector3i::Zero;
    REQUIRE(reverse_zero.x == 0);
    REQUIRE(reverse_zero.y == 0);
    REQUIRE(reverse_zero.z == 0);
    Vector3f reverse_full = -Vector3f(1.3f, -3.99f, 0.0f);
    REQUIRE(AlmostEqual(reverse_full.x, -1.3f));
    REQUIRE(AlmostEqual(reverse_full.y, 3.99f));
    REQUIRE(AlmostEqual(reverse_full.z, 0.0f));
    Vector3f double_reverse = -(-Vector3f::Ones);
    REQUIRE(double_reverse == Vector3f::Ones);
  }

  SECTION("Addition of vectors") {
    Vector3i a(1, -2, 0);
    Vector3i b(2, 1, 0);
    Vector3i result(3, -1, 0);
    REQUIRE((a + b) == result);
    REQUIRE((b + a) == result);
    REQUIRE((a + Vector3i::Zero) == a);
    REQUIRE((Vector3i::Zero + a) == a);
    REQUIRE((a + Vector3i::Ones) == Vector3i(2, -1, 1));
  }

  SECTION("Substraction of vectors") {
    Vector3i a(0, -1, 2);
    Vector3i b(3, 0, -2);
    Vector3i result(-3, -1, 4);
    REQUIRE((a - b) == result);
    REQUIRE((b - a) != result);
    REQUIRE((a - Vector3i::Zero) == a);
    REQUIRE((Vector3i::Zero - a) == -a);
    REQUIRE((Vector3i::Ones - b) == Vector3i(-2, 1, 3));
  }

  SECTION("Multiplication of vector and scalar") {
    Vector3i a(1, -33, 0);
    float alfa = 3;
    Vector3i result(3, -99, 0);
    REQUIRE((a * alfa) == result);
    REQUIRE((alfa * a) == result);
    REQUIRE((0.0 * a) == Vector3i::Zero);
    REQUIRE((1 * a) == a);
    Vector3f b(-0.0f, 2.3f, -5.5f);
    REQUIRE((0.0f * b) == Vector3f::Zero);
    REQUIRE((alfa * Vector3f::Zero) == Vector3f::Zero);
    REQUIRE((alfa * Vector3f::Ones) == Vector3f(3, 3, 3));
  }

  SECTION("Magnitude of vector") {
    float ones_magnitude = Vector3f::Ones.Magnitude();
    REQUIRE(AlmostEqual(ones_magnitude, 1.73205f, 0.0001f));
    float zero_magnitude = Vector3i::Zero.Magnitude();
    REQUIRE(AlmostEqual(zero_magnitude, 0.0f));
  }

  SECTION("Vector normalization") {
    auto ones_normalized = Vector3f::Ones.Normalize();
    REQUIRE(AlmostEqual(ones_normalized.x, 0.57735f, 0.0001f));
    REQUIRE(AlmostEqual(ones_normalized.y, 0.57735f, 0.0001f));
    REQUIRE(AlmostEqual(ones_normalized.z, 0.57735f, 0.0001f));
    float ones_magnitude = ones_normalized.Magnitude();
    REQUIRE(AlmostEqual(ones_magnitude, 1.0f));
    auto zero_normalized = Vector3i::Zero.Normalize();
    float zero_magnitude = zero_normalized.Magnitude();
    REQUIRE(AlmostEqual(zero_magnitude, 0.0f));
  }

  SECTION("Vectors (in)equality") {
    Vector3f a(2.5f, -1.2f + 2.0f, -0.3f);
    Vector3f b(4.5f - 2.0f, 0.8f, 0.0f - 0.3f);
    Vector3f c(1.3f, 2.2f, -0.35f);
    REQUIRE(a == b);
    REQUIRE(!(a != b));
    REQUIRE(a != c);
    REQUIRE(b != c);
    REQUIRE(c == c);
  }
}
