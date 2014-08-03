#pragma once

#include <cmath>

namespace aff {
  namespace math {

template<typename T>
class Vector2;

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;

template<typename T>
class Vector2
{
public:
  T x, y;

  Vector2<T>() : x(0), y(0) {}
  Vector2<T>(T _x, T _y) : x(_x), y(_y) {}

  inline float Magnitude() const;
  inline Vector2<T> Normalize() const;

  inline Vector2<T>& operator=(const Vector2<T>& vector);
  inline Vector2<T>& operator+=(const Vector2<T>& vector);
  inline Vector2<T>& operator-=(const Vector2<T>& vector);
  inline Vector2<T>& operator*=(float scalar);
  inline Vector2<T>& operator/=(float scalar);
  inline Vector2<T> operator-() const;

  static const Vector2<T> Zero;
  static const Vector2<T> Ones;
  static const Vector2<T> Base_1;
  static const Vector2<T> Base_2;
};

template<typename T>
float Vector2<T>::Magnitude() const
{
  return std::sqrt(static_cast<float>(x*x + y*y));
}

template<typename T>
Vector2<T> Vector2<T>::Normalize() const
{
  float magnitude = Magnitude();
  return Vector2<T>(
    static_cast<T>(x / magnitude),
    static_cast<T>(y / magnitude));
}

template<typename T>
Vector2<T>& Vector2<T>::operator=(const Vector2<T>& vector)
{
  x = vector.x;
  y = vector.y;
  return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& vector)
{
  x += vector.x;
  y += vector.y;
  return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& vector)
{
  x -= vector.x;
  y -= vector.y;
  return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(float scalar)
{
  x *= scalar;
  y *= scalar;
  return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(float scalar)
{
  x /= scalar;
  y /= scalar;
  return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator-() const
{
  return Vector2<T>(-x, -y);
}

/*** Global operators ***/
template<typename T>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
{
  return Vector2<T>(left.x + right.x, left.y + right.y);
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
{
  return Vector2<T>(left.x - right.x, left.y - right.y);
}

template<typename T>
Vector2<T> operator*(float scalar, const Vector2<T>& vector)
{
  return Vector2<T>(
    static_cast<T>(vector.x * scalar),
    static_cast<T>(vector.y * scalar));
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& vector, float scalar)
{
  return Vector2<T>(
    static_cast<T>(vector.x * scalar),
    static_cast<T>(vector.y * scalar));
}

template<typename T>
Vector2<T> operator/(const Vector2<T>& vector, float scalar)
{
  return Vector2<T>(
    static_cast<T>(vector.x / scalar),
    static_cast<T>(vector.y / scalar));
}

template<typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right)
{
  return left.x == right.x && left.y == right.y;
}

template<> 
bool operator==(const Vector2f& left, const Vector2f& right);

template<typename T>
bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
{
  return !(left == right);
}

/*** Predefined values ***/
template<typename T>
const Vector2<T> Vector2<T>::Zero = Vector2<T>(0, 0);
template<typename T>
const Vector2<T> Vector2<T>::Ones = Vector2<T>(1, 1);
template<typename T>
const Vector2<T> Vector2<T>::Base_1 = Vector2<T>(1, 0);
template<typename T>
const Vector2<T> Vector2<T>::Base_2 = Vector2<T>(0, 1);

// ~~ aff::math::Vector2  
}}
