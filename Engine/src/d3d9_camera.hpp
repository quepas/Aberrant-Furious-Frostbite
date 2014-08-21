#pragma once

#include "core_camera.hpp"

#include <d3dx9.h>

namespace aff {
  namespace d3d9 {

class Camera : public core::Camera
{
public:
  Camera();
  ~Camera();

  void MoveForward(float unit) override;
  void Strafe(float unit) override;
  void DoYaw(float degree) override;
  void DoPitch(float degree) override;
  void DoRoll(float degree) override;

  void Update() override;

  const D3DXMATRIX& view_matrix() const { return view_matrix_; }
  const D3DXMATRIX& projection_matrix() const { projection_matrix_; }

private:
  D3DXMATRIX view_matrix_;
  D3DXMATRIX projection_matrix_;

  D3DXVECTOR3 movement_;
  D3DXVECTOR3 look_;
  D3DXVECTOR3 right_;

  void CalculatePerspectiveMatrix();
  void CalculateViewMatrix();

};

}}
// ~~ aff::d3d9::Camera
