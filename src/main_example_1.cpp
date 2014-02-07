#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <d3dx9.h>

#include "util/util_random.hpp"
#include "win32/win32_window_builder.hpp"
#include "util/util_logger.hpp"
#include "d3d9/d3d9_texture.hpp"
#include "d3d9/d3d9_effect.hpp"

using namespace aff;

int main()
{
  util::Logger& logger = util::Logger("main");
  logger.Info("Aberrant-Furious-Frostbite");
  
  win32::WindowBuilder window_builder;
  auto window = window_builder
    .ClassStyle(CS_HREDRAW | CS_VREDRAW)
    .Position(600, 100)
    .Dimension(640, 480)
    .Label("Aberrant-Furious-Frostbite")
    .Build();
  window.CreateAndShow();
  logger.Info("Window created. Showing it!");
 
  // D3D
  IDirect3D9* direct_3d9 = Direct3DCreate9(D3D_SDK_VERSION);
  D3DPRESENT_PARAMETERS present_parameters;
  ZeroMemory(&present_parameters, sizeof(present_parameters));
  present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
  present_parameters.Windowed = true;
  present_parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
  present_parameters.EnableAutoDepthStencil = true;
  present_parameters.AutoDepthStencilFormat = D3DFMT_D16;

  IDirect3DDevice9* device_3d9;
  direct_3d9->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    window.hwnd(),
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &present_parameters,
    &device_3d9);

  if (!device_3d9)
    logger.Fatal("Direct3D device is null");

  device_3d9->SetRenderState(D3DRS_ZENABLE, true);
  device_3d9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

  MSG msg;
  bool done = false;
  while (!done)
  {
    if (PeekMessage(&msg, window.hwnd(), NULL, NULL, PM_REMOVE))
    {
      if (msg.message == WM_QUIT) done = true;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      if (GetKeyState(VK_ESCAPE) & 0x0800) done = true;
      
      device_3d9->Clear(0, NULL, D3DCLEAR_TARGET, 0xff00ff00, 1, 0);
      device_3d9->BeginScene();
      // here goes render code 
      device_3d9->EndScene();
      device_3d9->Present(NULL, NULL, NULL, NULL);
    }
  }

  // clean up
  device_3d9->Release();
  direct_3d9->Release();

  return msg.wParam;
}