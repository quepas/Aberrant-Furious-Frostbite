#include "core_camera.hpp"

namespace aff {
  namespace core {

Camera::Camera()
  : field_of_view_(90.0f),
    near_clipping_plane_(1.0f),
    far_clipping_plane_(100.0f),
    view_ratio_(4.0f / 3.0f),
    position_(0.0f, 0.0f, -3.0f),
    look_at_(0.0f, 0.0f, 0.0f)
{

}

Camera::Camera(const math::Vector3f& position, const math::Vector3f& look_at, float field_of_view)
  : field_of_view_(field_of_view),
    near_clipping_plane_(1.0f),
    far_clipping_plane_(100.0f),
    view_ratio_(4.0f / 3.0f),
    position_(position),
    look_at_(look_at)
{

}

Camera::~Camera()
{

}

void Camera::MoveTo(const math::Vector3f& position)
{
  position_ = position;
}

void Camera::LookAt(const math::Vector3f& look_at)
{
  look_at_ = look_at;
}

void Camera::SetFieldOfView(float fov)
{
  field_of_view_ = fov;
}

void Camera::SetClippingPlanes(float near, float far)
{
  near_clipping_plane_ = near;
  far_clipping_plane_ = far;
}

void Camera::SetViewRatio(float view_ratio)
{
  view_ratio_ = view_ratio;
}

}}
// ~~ aff::core::Camera
