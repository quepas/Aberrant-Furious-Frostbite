#include <iostream>
#include <Windows.h>

#include "util/util_random.hpp"
#include "win32/win32_window_builder.hpp"

using namespace aff;

int main()
{
  std::cout << "Aberrant-Furious-Frostbite" << std::endl;

  win32::WindowBuilder window_builder;
  auto window = window_builder
    .ClassStyle(CS_HREDRAW | CS_VREDRAW)
    .Position(100, 100)
    .Dimension(800, 600)
    .Label("Aberrant-Furious-Frostbite")
    .Build();
  window.CreateAndShow();
 
  MSG msg;
  bool done = false;
  while (!done)
  {
    PeekMessage(&msg, window.hwnd(), NULL, NULL, PM_REMOVE);

    if (msg.message == WM_QUIT)
      done = true;
    else 
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  return msg.wParam;
}