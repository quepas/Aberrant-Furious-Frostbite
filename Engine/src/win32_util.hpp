#pragma once

#include <windows.h>

namespace aff {
  namespace win32 {

bool CheckMessages(MSG& msg, const HWND& hwnd);
void HandleMessage(MSG& msg);

}}
// ~~ aff::win32