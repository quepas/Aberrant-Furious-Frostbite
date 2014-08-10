#pragma once

#include "core_camera.hpp"
#include "core_entity.hpp"
#include "d3d9_effect.hpp"
#include "d3d9_render_storage.hpp"
#include "d3d9_x_model.hpp"
#include "gfx_renderer.hpp"
#include "gfx_model_3d.hpp"

#include <d3dx9.h>

namespace aff {
  namespace d3d9 {

class Renderer : public gfx::Renderer
{
public:
  Renderer(D3DPRESENT_PARAMETERS present_parameters, HWND hwnd);
  ~Renderer();

  virtual void Initialize();
  virtual void Release();
  virtual bool IsCorrect();

  virtual void BeforeRendering();
  virtual void AfterRendering();

  // track entity resources
  void TrackEntity(const core::Entity& entity);
  virtual void RenderEntity(const core::Entity& entity);
  virtual void SetCurrentCamera(const core::Camera& camera);

  D3DXMATRIX PrepareEntityMatrix(const core::Entity& entity);
  void RenderXModel(const XModel& model, const Effect& effect, const D3DXMATRIX& model_matrix);
  void RenderRawModel(const gfx::Model3d& model, const Effect& effect, const D3DXMATRIX& model_matrix);

  IDirect3DDevice9* device() { return device_; }
  IDirect3D9* direct() { return direct_; }

private:
  D3DPRESENT_PARAMETERS present_parameters_;
  HWND hwnd_;

  IDirect3D9* direct_;
  IDirect3DDevice9* device_;

  D3DXMATRIX view_;
  D3DXMATRIX projection_;

  RenderStorage* storage_;
};

}}
// ~~ aff::d3d9::Renderer