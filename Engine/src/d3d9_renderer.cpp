#include "d3d9_renderer.hpp"

namespace aff {
  namespace d3d9 {

Renderer::Renderer(D3DPRESENT_PARAMETERS present_parameters, HWND hwnd)
  : present_parameters_(present_parameters),
    hwnd_(hwnd)
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialize()
{
  direct_ = Direct3DCreate9(D3D_SDK_VERSION);
  if (FAILED(direct_->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    hwnd_,
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &present_parameters_,
    &device_)))
  {
    //logger.Fatal("Direct3D device is null");
  }

  device_->SetRenderState(D3DRS_ZENABLE, true);
  device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void Renderer::Release()
{
  device_->Release();
  direct_->Release();
}

bool Renderer::IsCorrect()
{
  return device_ != nullptr && direct_ != nullptr;
}

void Renderer::BeforeRendering()
{
  device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff00ff00, 1, 0);
  device_->BeginScene();
}

void Renderer::AfterRendering()
{
  device_->EndScene();
  device_->Present(NULL, NULL, NULL, NULL);
}

}}
// ~~ aff::d3d9::Renderer
