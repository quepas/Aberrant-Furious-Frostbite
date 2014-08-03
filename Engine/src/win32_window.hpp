#pragma once

#include <string>
#include <Windows.h>

#include "util_logger.hpp"

namespace aff {
  namespace win32 {

class Window
{
public:
  struct CreateData;
  Window(WNDCLASSEX extended_class, CreateData create_data);
  ~Window();

  HWND Create();
  HWND CreateAndShow();
  inline HWND hwnd() const;
  inline const WNDCLASSEX& extended_class();
  inline const CreateData& create_data();

  static void DefaultWndClassEx(WNDCLASSEX& wnd_class_ex);
  static void DefaultWndCreateData(CreateData& create_data);
  
  struct CreateData
  {
    DWORD style;
    DWORD extended_style;
    LPCSTR window_label;
    int position_x, position_y;
    int width, height;
    HWND parent_window;
    HMENU menu;
    LPVOID extra_parameter;
  };

private:
  HWND hwnd_;
  WNDCLASSEX extended_class_;
  CreateData create_data_;
  util::Logger logger_;
};

inline HWND Window::hwnd() const {
  return hwnd_;
}

inline const WNDCLASSEX& Window::extended_class() {
  return extended_class_;
}

inline const Window::CreateData& Window::create_data() {
  return create_data_;
}

// ~~ aff::win32::Window
}}
