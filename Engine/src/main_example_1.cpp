#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <d3dx9.h>

#include "core_entity.hpp"
#include "util_random.hpp"
#include "win32_window_builder.hpp"
#include "win32_input.hpp"
#include "win32_util.hpp"
#include "util_logger.hpp"
#include "d3d9_texture.hpp"
#include "d3d9_effect.hpp"
#include "d3d9_x_model.hpp"
#include "d3d9_device_caps.hpp"
#include "d3d9_renderer.hpp"

using namespace aff;
using namespace std;

int main()
{
  util::Logger& logger = util::Logger("main");
  logger.Info("Aberrant-Furious-Frostbite");
  
  auto window = win32::WindowBuilder
    ::Start()
    .ClassStyle(CS_HREDRAW | CS_VREDRAW)
    .Position(600, 100)
    .Dimension(640, 480)
    .Label("Aberrant-Furious-Frostbite")
    .Build();
  window.CreateAndShow();
  logger.Info("Window created. Showing it!");
  
  // D3D
  D3DPRESENT_PARAMETERS present_parameters;
  ZeroMemory(&present_parameters, sizeof(present_parameters));
  present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
  present_parameters.Windowed = true;
  present_parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
  present_parameters.EnableAutoDepthStencil = true;
  present_parameters.AutoDepthStencilFormat = D3DFMT_D16;

  d3d9::Renderer renderer(present_parameters, window.hwnd());
  renderer.Initialize();

  // D3D info
  const d3d9::DeviceCaps& device_caps(renderer.direct());
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

  d3d9::XModel model("resource/model/dwarf.x", renderer.device());
  d3d9::Effect effect("resource/shader/identity.fx", renderer.device());
  core::Entity entity(&model, &effect);
  entity.MoveTo(math::Vector3f(0.0f, 0.0f, 5.0f));
  core::Camera camera;
  renderer.SetCurrentCamera(camera);

  MSG msg;
  bool done = false;
  win32::Input input;
  while (!done)
  {
    if (win32::CheckMessages(msg, window.hwnd()))
    {
      if (msg.message == WM_QUIT) done = true;
      input.RetriveInput(msg);
      win32::HandleMessage(msg);
    }
    else
    {
      if (win32::Input::IsKeyPressed(VK_ESCAPE)) done = true;
      
      renderer.BeforeRendering();
      // here goes render code 
      if (win32::Input::IsKeyPressed(VK_UP))
        entity.MoveBy(math::Vector3f(0.0f, 0.0f, 0.1f));
      if (win32::Input::IsKeyPressed(VK_DOWN))
        entity.MoveBy(math::Vector3f(0.0f, 0.0f, -0.1f));

      entity.RotateBy(math::Vector3f(0.01f, 0.0f, 0.0f));

      renderer.RenderEntity(entity);
      renderer.AfterRendering();
    }
  }
  renderer.Release();

  return msg.wParam;
}
