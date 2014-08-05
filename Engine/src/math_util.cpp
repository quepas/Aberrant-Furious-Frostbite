#include "math_util.hpp"

using std::abs;

namespace aff {
  namespace math {

bool AlmostEqual(float a, float b, float eps /*= 0.00001f*/)
{
  return abs(a - b) < eps;
}

float Rad2Deg(float rad)
{
  return rad * (180.0f / PIf);
}

float Deg2Rad(float deg)
{
  return deg * (PIf / 180.0f);
}

}}
// ~~ aff::math
