#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <d3dx9.h>

#include "util_random.hpp"
#include "win32_window_builder.hpp"
#include "win32_input.hpp"
#include "util_logger.hpp"
#include "d3d9_texture.hpp"
#include "d3d9_effect.hpp"
#include "d3d9_x_model.hpp"
#include "d3d9_device_caps.hpp"

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

  d3d9::XModel model("resource/model/dwarf.x", device_3d9);
  d3d9::Effect effect("resource/shader/identity.fx", device_3d9);

  device_3d9->SetRenderState(D3DRS_ZENABLE, true);
  device_3d9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

  D3DXMATRIX matrix_view;
  D3DXMATRIX matrix_projection;

  D3DXMatrixPerspectiveFovLH
    (&matrix_projection, D3DXToRadian(90), 4 / 3.0f, 1, 100);
  D3DXMatrixLookAtLH(
    &matrix_view, 
    &D3DXVECTOR3(0.0f, 0.0f, -3.0f), 
    &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
    &D3DXVECTOR3(0.0f, 1.0f, 0.0f));  

  MSG msg;
  bool done = false;
  win32::Input input;
  while (!done)
  {
    if (PeekMessage(&msg, window.hwnd(), NULL, NULL, PM_REMOVE))
    {
      if (msg.message == WM_QUIT) done = true;
      input.RetriveInput(msg);
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      if (win32::Input::IsKeyPressed(VK_ESCAPE)) done = true;
      
      device_3d9->Clear
        (0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff00ff00, 1, 0);
      device_3d9->BeginScene();

      // here goes render code 
      static float angle = 0.0f;
      static float z_translation = 5.0f;

      if (win32::Input::IsKeyPressed(VK_UP))
        z_translation += 0.1f;
      if (win32::Input::IsKeyPressed(VK_DOWN))
        z_translation -= 0.1f;

      angle += 0.01f;

      if (angle > 360.0f)
        angle = 0.01f;

      D3DXMATRIX matrix_rotation, matrix_translation, matrix_world;
      D3DXMatrixTranslation(&matrix_translation, 0.0f, 0.0f, z_translation);
      D3DXMatrixRotationAxis
        (&matrix_rotation, &D3DXVECTOR3(1.0f, 1.0f, 0.0f), angle);
      matrix_world = matrix_rotation * matrix_translation;
      D3DXMATRIX matrix_world_view_proj = 
        matrix_world * matrix_view * matrix_projection;
      
      if (effect.IsCorrect() && model.IsCorrect()) {
        const auto& effect_data = effect.d3d9_effect();
        effect_data->SetMatrix
          ("matrix_world_view_proj", &matrix_world_view_proj);

        UINT passes;
        D3DXHANDLE tech;
        effect_data->FindNextValidTechnique(0, &tech);
        effect_data->SetTechnique(tech);
        effect_data->Begin(&passes, 0);
        for (UINT pass = 0; pass < passes; ++pass)
        {
          effect_data->BeginPass(pass);

          const auto& materials = model.textures();
          for (UINT i = 0; i < model.subset_number(); ++i) {
            if (i < materials.size())
              effect_data->SetTexture("tex0", materials[i]->d3d9_texture());
            effect_data->CommitChanges();
            model.mesh()->DrawSubset(i);
          }

          effect_data->EndPass();
        }
        effect_data->End();
      }

      device_3d9->EndScene();
      device_3d9->Present(NULL, NULL, NULL, NULL);
    }
  }

  // clean up
  device_3d9->Release();
  direct_3d9->Release();

  return msg.wParam;
}