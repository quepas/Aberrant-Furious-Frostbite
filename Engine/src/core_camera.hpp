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

  // camera manipulation
  virtual void MoveForward(float unit);
  virtual void Strafe(float unit);
  virtual void DoYaw(float degree);
  virtual void DoPitch(float degree);
  virtual void DoRoll(float degree);

  virtual void Update() override;

  void LookAt(const math::Vector3f& look_at);

  void SetFieldOfView(float fov);
  void SetClippingPlanes(float near, float far);
  void SetViewRatio(float view_ratio);

  float field_of_view() const { return field_of_view_; }
  float near_clipping_plane() const { return near_clipping_plane_; }
  float far_clipping_plane() const { return far_clipping_plane_; }
  float view_ratio() const { return view_ratio_; }
  const math::Vector3f& look_at() const { return look_at_; }
  const math::Vector3f& up() const { return up_; }

protected:
  float field_of_view_;
  float near_clipping_plane_;
  float far_clipping_plane_;
  float view_ratio_;

  math::Vector3f look_at_;
  math::Vector3f up_;
};

}}
// ~~ aff::core::Camera
