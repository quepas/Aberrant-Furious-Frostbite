#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <d3dx9.h>

#include "util/util_random.hpp"
#include "win32/win32_window_builder.hpp"
#include "util/util_logger.hpp"
#include "d3d9/d3d9_texture.hpp"
#include "d3d9/d3d9_effect.hpp"
#include "d3d9/d3d9_x_model.hpp"
#include "d3d9/d3d9_device_caps.hpp"

using namespace aff;
using namespace std;

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

  // D3D info
  const d3d9::DeviceCaps& device_caps(direct_3d9);
  logger.Info("==== GFX adapter display info ====");
  logger.Info("\tAdapter Count: " 
    + std::to_string(device_caps.GetAdapterCount()));
  auto display_mode = device_caps.GetAdapterDisplayMode();
  logger.Info("\tScreen resolution: " + to_string(display_mode.Width) 
    + "x" + to_string(display_mode.Height));
  logger.Info("\tRefresh rate: " + to_string(display_mode.RefreshRate));
  logger.Info("\tFormat: " + to_string(display_mode.Format));

  logger.Info("==== GFX device info ====");
  auto adapter_identifier = device_caps.GetAdapterIdentifier();
  logger.Info("\tDeviceId: " + to_string(adapter_identifier.DeviceId));
  logger.Info("\tDeviceName: " + string(adapter_identifier.DeviceName));
  logger.Info("\tDriver: " + string(adapter_identifier.Driver));  
  logger.Info("\tDescription: " + string(adapter_identifier.Description));

  IDirect3DDevice9* device_3d9;
  if (FAILED(direct_3d9->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    window.hwnd(),
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &present_parameters,
    &device_3d9)))
  {
    logger.Fatal("Direct3D device is null");
    return EXIT_FAILURE;
  }  

  d3d9::XModel model("resource/model/plane.x", device_3d9);

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