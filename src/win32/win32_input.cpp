#include "win32_input.hpp"

namespace aff {
  namespace win32 {

Input::Input()
{
}

Input::~Input()
{
}

bool Input::RetriveInput(MSG msg)
{
  LPARAM param;
  POINTS point;

  switch (msg.message)
  {
  case WM_MOUSEMOVE:
    mouse_.last.x = mouse_.current.x;
    mouse_.last.y = mouse_.current.y;
    param = msg.lParam;
    point = MAKEPOINTS(param);
    mouse_.current.x = point.x;
    mouse_.current.y = point.y;    
    mouse_.diff.x = mouse_.last.x - mouse_.current.x;
    mouse_.diff.y = mouse_.last.y - mouse_.current.y;
    return true;
  case WM_INPUT:
    return true;
  default:
    return false;
  }
}

// ~~ aff::win32::Input
}}
