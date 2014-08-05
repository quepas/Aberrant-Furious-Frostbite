#pragma once

#include <cmath>

namespace aff {
  namespace math {

template<typename T>
class Vector3;

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;

template<typename T>
class Vector3
{
public:
  T x, y, z;

  Vector3<T>() : x(0), y(0), z(0) {}
  Vector3<T>(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

  inline float Magnitude() const;
  inline Vector3<T> Normalize() const;

  inline Vector3<T>& operator=(const Vector3<T>& vector);
  inline Vector3<T>& operator+=(const Vector3<T>& vector);
  inline Vector3<T>& operator-=(const Vector3<T>& vector);
  inline Vector3<T>& operator*=(float scalar);
  inline Vector3<T>& operator/=(float scalar);
  inline Vector3<T> operator-() const;

  static const Vector3<T> Zero;
  static const Vector3<T> Ones;
  static const Vector3<T> Base_1;
  static const Vector3<T> Base_2;
  static const Vector3<T> Base_3;
};

template<typename T>
float Vector3<T>::Magnitude() const
{
  return std::sqrt(static_cast<float>(x*x + y*y + z*z));
}

template<typename T>
Vector3<T> Vector3<T>::Normalize() const
{
  float magnitude = Magnitude();
  return Vector3<T>(
    static_cast<T>(x / magnitude),
    static_cast<T>(y / magnitude),
    static_cast<T>(z / magnitude));
}

template<typename T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& vector)
{
  x = vector.x;
  y = vector.y;
  z = vector.z;
  return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vector)
{
  x += vector.x;
  y += vector.y;
  z += vector.z;
  return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vector)
{
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
  return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator*=(float scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator/=(float scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator-() const
{
  return Vector3<T>(-x, -y, -z);
}

/*** Global operators ***/
template<typename T>
Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
{
  return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template<typename T>
Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
{
  return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template<typename T>
Vector3<T> operator*(float scalar, const Vector3<T>& vector)
{
  return Vector3<T>(
    static_cast<T>(vector.x * scalar),
    static_cast<T>(vector.y * scalar),
    static_cast<T>(vector.z * scalar));
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& vector, float scalar)
{
  return Vector3<T>(
    static_cast<T>(vector.x * scalar),
    static_cast<T>(vector.y * scalar),
    static_cast<T>(vector.z * scalar));
}

template<typename T>
Vector3<T> operator/(const Vector3<T>& vector, float scalar)
{
  return Vector3<T>(
    static_cast<T>(vector.x / scalar),
    static_cast<T>(vector.y / scalar),
    static_cast<T>(vector.z / scalar));
}

template<typename T>
bool operator==(const Vector3<T>& left, const Vector3<T>& right)
{
  return left.x == right.x && left.y == right.y && left.z == right.z;
}

template<>
bool operator==(const Vector3f& left, const Vector3f& right);

template<typename T>
bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
{
  return !(left == right);
}

/*** Predefined values ***/
template<typename T>
const Vector3<T> Vector3<T>::Zero = Vector3<T>(0, 0, 0);
template<typename T>
const Vector3<T> Vector3<T>::Ones = Vector3<T>(1, 1, 1);
template<typename T>
const Vector3<T> Vector3<T>::Base_1 = Vector3<T>(1, 0, 0);
template<typename T>
const Vector3<T> Vector3<T>::Base_2 = Vector3<T>(0, 1, 0);
template<typename T>
const Vector3<T> Vector3<T>::Base_3 = Vector3<T>(0, 0, 1);

// ~~ aff::math::Vector3
}}
