#pragma once

#include "math_vector3.hpp"

namespace aff {
  namespace core {

class SceneEntity
{
public:
  SceneEntity()
    : position_(0.0f, 0.0f, 0.0f),
      angle_(0.0f, 0.0f, 0.0f),
      visible_(true)  {}
  virtual ~SceneEntity() {}

  inline void MoveTo(const math::Vector3f& position) { position_ = position; }
  inline void MoveBy(const math::Vector3f& distance) { position_ = distance; }
  inline void RotateTo(const math::Vector3f& rotation) { angle_ = rotation; }
  inline void RotateBy(const math::Vector3f& angle) { angle_ = angle; }
  inline void SetVisibility(bool visible) { visible_ = visible; }

  inline const math::Vector3f& position() const { return position_; }
  inline const math::Vector3f& angle() const { return angle_; }
  inline bool is_visible() const { return visible_; }

protected:
  math::Vector3f position_;
  math::Vector3f angle_;
  bool visible_;
};

}}
// ~~ aff::core::SceneEntity
