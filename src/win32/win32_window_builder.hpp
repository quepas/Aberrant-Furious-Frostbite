#pragma once

#include "win32_window.hpp"

namespace aff {
  namespace win32 {

class WindowBuilder
{
public:
  WindowBuilder();
  ~WindowBuilder();

  // Window class data
  WindowBuilder& AppInstance(HINSTANCE app_instance);
  WindowBuilder& ClassStyle(UINT class_style);
  WindowBuilder& ClassExtra(int class_extra);
  WindowBuilder& ClassName(LPCSTR class_name);
  WindowBuilder& WndProcedure(WNDPROC wnd_procedure);
  WindowBuilder& WndExtra(int wnd_extra);
  WindowBuilder& BigIcon(HICON big_icon);
  WindowBuilder& SmallIcon(HICON small_icon);
  WindowBuilder& Cursor(HCURSOR cursor);
  WindowBuilder& BackgroundColor(HBRUSH color);
  WindowBuilder& MenuName(LPCSTR menu_name);
  
  // Window create data
  WindowBuilder& Style(DWORD style);
  WindowBuilder& ExtendedStyle(DWORD extended_style);
  WindowBuilder& Label(LPCSTR name);
  WindowBuilder& PositionX(int x);
  WindowBuilder& PositionY(int y);
  WindowBuilder& Position(int x, int y);
  WindowBuilder& Width(int width);
  WindowBuilder& Height(int height);
  WindowBuilder& Dimension(int width, int height);
  WindowBuilder& ParentWindow(HWND parent_window);
  WindowBuilder& Menu(HMENU menu);
  WindowBuilder& ExtraParameter(LPVOID extra_parameter);

  Window& Build();
  void Reset();

private:
  WNDCLASSEX extended_class_;
  Window::CreateData create_data_;
};

// ~~ aff::win32::WindowBuilder
}}
