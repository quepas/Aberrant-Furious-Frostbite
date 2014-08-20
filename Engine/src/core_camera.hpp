#pragma once

#include "core_scene_entity.hpp"
#include "math_vector3.hpp"

namespace aff {
  namespace core {

class Camera : public SceneEntity
{
public:
  Camera();
  Camera(const math::Vector3f& positon, const math::Vector3f& look_at, float field_of_view);
  virtual ~Camera();

  float field_of_view() const { return field_of_view_; }
  float near_clipping_plane() const { return near_clipping_plane_; }
  float far_clipping_plane() const { return far_clipping_plane_; }
  float view_ratio() const { return view_ratio_; }
  math::Vector3f look_at() const { return look_at_; }

  void LookAt(const math::Vector3f& look_at);

  void SetFieldOfView(float fov);
  void SetClippingPlanes(float near, float far);
  void SetViewRatio(float view_ratio);

protected:
  float field_of_view_;
  float near_clipping_plane_;
  float far_clipping_plane_;
  float view_ratio_;

  math::Vector3f look_at_;
};

}}
// ~~ aff::core::Camera
