#pragma once

#include "win32_util.hpp"

namespace aff {
  namespace win32 {

bool CheckMessages(MSG& msg, const HWND& hwnd)
{
  return static_cast<bool>(PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE));
}

void HandleMessage(MSG& msg)
{
  TranslateMessage(&msg);
  DispatchMessage(&msg);
}

}}
// ~~ aff::win32
