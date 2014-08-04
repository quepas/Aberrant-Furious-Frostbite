#pragma once

#include "gfx_renderer.hpp"

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

  IDirect3DDevice9* device() { return device_; }
  IDirect3D9* direct() { return direct_; }

private:
  D3DPRESENT_PARAMETERS present_parameters_;
  HWND hwnd_;

  IDirect3D9* direct_;
  IDirect3DDevice9* device_;
};

}}
// ~~ aff::d3d9::Renderer