#include "math_util.hpp"

using std::abs;

namespace aff {
  namespace math {

bool AlmostEqual(float a, float b, float eps /*= 0.00001f*/)
{
  return abs(a - b) < eps;
}

}}
// ~~ aff::math
