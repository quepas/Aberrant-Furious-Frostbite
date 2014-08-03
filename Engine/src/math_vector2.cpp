#include "math_vector2.hpp"
#include "math_util.hpp"

namespace aff {
  namespace math {

template<>
bool operator==(const Vector2f& left, const Vector2f& right)
{
  return AlmostEqual(left.x, right.x) && AlmostEqual(left.y, right.y);
}

}}
// ~~ aff::math::Vector2
