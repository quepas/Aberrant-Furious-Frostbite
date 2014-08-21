#include "d3d9_camera.hpp"

#include "math_util.hpp"

using aff::math::ToAffVector3f;
using aff::math::ToD3DXVector3;

namespace aff {
  namespace d3d9 {

Camera::Camera()
  : movement_(0.0f, 0.0f, 0.0f)
{
  D3DXMatrixIdentity(&view_matrix_);
  D3DXMatrixIdentity(&projection_matrix_);

  auto raw_look = ToD3DXVector3(look_at_ - position_);
  D3DXVec3Normalize(&look_, &raw_look);
  D3DXVec3Cross(&right_, &ToD3DXVector3(up_), &look_);
  D3DXVec3Normalize(&right_, &right_);

  CalculatePerspectiveMatrix();
  CalculateViewMatrix();
}

Camera::~Camera()
{

}

void Camera::MoveForward(float unit)
{
  movement_ += look_ * unit;
}

void Camera::Strafe(float unit)
{
  movement_ += right_ * unit;
}

void Camera::DoYaw(float degree)
{
  float radians = D3DXToRadian(degree);
  D3DXMATRIX rotation;
  D3DXMatrixRotationAxis(&rotation, &ToD3DXVector3(up_), radians);
  D3DXVec3TransformNormal(&right_, &right_, &rotation);
  D3DXVec3TransformNormal(&look_, &look_, &rotation);
}

void Camera::DoPitch(float degree)
{
  float radians = D3DXToRadian(degree);
  D3DXMATRIX rotation;
  D3DXMatrixRotationAxis(&rotation, &right_, radians);
  D3DXVECTOR3 up;
  D3DXVec3TransformNormal(&up, &ToD3DXVector3(up_), &rotation);
  up_ = ToAffVector3f(up);
  D3DXVec3TransformNormal(&look_, &look_, &rotation);
}

void Camera::DoRoll(float degree)
{
  float radians = D3DXToRadian(degree);
}

void Camera::Update()
{
  position_ += ToAffVector3f(movement_);
  movement_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  look_at_ = position_ + ToAffVector3f(look_);

  D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  CalculateViewMatrix();

  right_ = { view_matrix_._11, view_matrix_._21, view_matrix_._31 };
     up_ = { view_matrix_._12, view_matrix_._22, view_matrix_._32 };
   look_ = { view_matrix_._13, view_matrix_._23, view_matrix_._33 };
}

void Camera::CalculatePerspectiveMatrix()
{
  D3DXMatrixPerspectiveFovLH(
    &projection_matrix_,
    D3DXToRadian(field_of_view_),
    view_ratio_,
    near_clipping_plane_,
    far_clipping_plane_);
}

void Camera::CalculateViewMatrix()
{
  D3DXMatrixLookAtLH(
    &view_matrix_,
    &ToD3DXVector3(position_),
    &ToD3DXVector3(look_at_),
    &ToD3DXVector3(up_));
}

}}
// ~~ aff::d3d9::Camera
