#pragma once

namespace aff {
  namespace math {

template <typename T>
class Vector2;

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

template<typename T>
class Vector2
{
public:
  const T x_, y_;

  Vector2<T>() : x_(0), y_(0) {}
  Vector2<T>(T x, T y) : x_(x), y_(y) {}

  inline Vector2<T> operator+(const Vector2& right) const;
  inline Vector2<T> operator-(const Vector2& right) const;
};

template<typename T>
Vector2<T> aff::math::Vector2<T>::operator+(const Vector2& right) const
{
  return Vector2<T>(x_ + right.x_, y_ + right.y_);
}

template<typename T>
Vector2<T> aff::math::Vector2<T>::operator-(const Vector2& right) const
{
  return Vector2<T>(x_ - right.x_, y_ - right.y_);
}

// ~~ aff::math::Vector2  
}}