#include "core_camera.hpp"

using aff::math::Vector3f;

namespace aff {
  namespace core {

Camera::Camera()
  : field_of_view_(90.0f),
    near_clipping_plane_(1.0f),
    far_clipping_plane_(100.0f),
    view_ratio_(4.0f / 3.0f),
    look_at_(0.0f, 0.0f, 0.0f),
    up_(0.0f, 1.0f, 0.0f)
{
  MoveTo(Vector3f(0.0f, 0.0f, -3.0f));
}

Camera::Camera(const math::Vector3f& position, const math::Vector3f& look_at, float field_of_view)
  : field_of_view_(field_of_view),
    near_clipping_plane_(1.0f),
    far_clipping_plane_(100.0f),
    view_ratio_(4.0f / 3.0f),
    look_at_(look_at),
    up_(0.0f, 1.0f, 0.0f)
{
  MoveTo(Vector3f(0.0f, 0.0f, -3.0f));
}

Camera::~Camera()
{

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

void Camera::Strafe(float unit)
{
  Vector3f movement = Vector3f::Zero;
  Vector3f zaxis = (look_at_ - position_).Normalize();
  Vector3f xaxis = Vector3f::Cross({ 0.0f, 1.0f, 0.0f }, zaxis).Normalize();

  Vector3f right{ xaxis.x, xaxis.y, xaxis.z };
  right = right * unit;
  position_ += right;
  look_at_ += right;
}

void Camera::MoveForward(float unit)
{
  Vector3f movement = Vector3f::Zero;
  Vector3f zaxis = (look_at_ - position_).Normalize();

  Vector3f look{ zaxis.x, zaxis.y, zaxis.z };
  look = look * unit;
  position_ += look;
  look_at_ += look;
}

void Camera::DoYaw(float degree)
{
  Vector3f look{ sinf(degree), 0.0f, -cosf(degree) };
  look_at_ = look + position_;
}

void Camera::DoPitch(float degree)
{

}

void Camera::DoRoll(float degree)
{

}

void Camera::Update()
{
  Vector3f movement = Vector3f::Zero;
  Vector3f zaxis = (look_at_ - position_).Normalize();
  Vector3f xaxis = Vector3f::Cross({ 0.0f, 1.0f, 0.0f }, zaxis).Normalize();
  Vector3f yaxis = Vector3f::Cross(zaxis, xaxis);

  Vector3f right{ xaxis.x, yaxis.x, zaxis.x };
  Vector3f look{ zaxis.x, zaxis.y, zaxis.z };
}

}}
// ~~ aff::core::Camera
