#include "math_vector3.hpp"
#include "math_util.hpp"

namespace aff {
  namespace math {

template<>
bool operator==(const Vector3f& left, const Vector3f& right)
{
  return AlmostEqual(left.x, right.x) && AlmostEqual(left.y, right.y) && AlmostEqual(left.z, right.z);
}

}}
// ~~ aff::math::Vector3
