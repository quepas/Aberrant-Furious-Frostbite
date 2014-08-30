#pragma once

#include "math_vector3.hpp"

#include <cmath>
#include <d3dx9.h>

#undef near
#undef far

namespace aff {
  namespace math {

const double PI = 3.14159265358979323846;
const float PIf = static_cast<float>(PI);

bool AlmostEqual(float a, float b, float eps = 0.00001f);
float Rad2Deg(float rad);
float Deg2Rad(float deg);
template<typename T>
D3DXVECTOR3 ToD3DXVector3(const Vector3<T>& vector);
Vector3f ToAffVector3f(const D3DXVECTOR3& vector);

}}

template<typename T>
D3DXVECTOR3 aff::math::ToD3DXVector3(const Vector3<T>& vector)
{
  return D3DXVECTOR3(vector.x, vector.y, vector.z);
}

// ~~ aff::math
