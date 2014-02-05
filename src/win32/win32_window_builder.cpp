#include "win32_window_builder.hpp"

namespace aff {
  namespace win32 {

WindowBuilder::WindowBuilder()
{
  Reset();
}

WindowBuilder::~WindowBuilder()
{
}

Window& WindowBuilder::Build()
{
  return Window(extended_class_, create_data_);
}

void WindowBuilder::Reset()
{
  Window::DefaultWndClassEx(extended_class_);
  Window::DefaultWndCreateData(create_data_);
}

// Window class data
WindowBuilder& WindowBuilder::AppInstance(HINSTANCE app_instance)
{
  extended_class_.hInstance = app_instance;
  return *this;
}

WindowBuilder& WindowBuilder::ClassStyle(UINT class_style)
{
  extended_class_.style = class_style;
  return *this;
}

WindowBuilder& WindowBuilder::ClassExtra(int class_extra)
{
  extended_class_.cbClsExtra = class_extra;
  return *this;
}

WindowBuilder& WindowBuilder::ClassName(LPCSTR class_name)
{
  extended_class_.lpszClassName = class_name;
  return *this;
}

WindowBuilder& WindowBuilder::WndProcedure(WNDPROC wnd_procedure)
{
  extended_class_.lpfnWndProc = wnd_procedure;
  return *this;
}

WindowBuilder& WindowBuilder::WndExtra(int wnd_extra)
{
  extended_class_.cbWndExtra = wnd_extra;
  return *this;
}

WindowBuilder& WindowBuilder::BigIcon(HICON big_icon)
{
  extended_class_.hIcon = big_icon;
  return *this;
}

WindowBuilder& WindowBuilder::SmallIcon(HICON small_icon)
{
  extended_class_.hIconSm = small_icon;
  return *this;
}

WindowBuilder& WindowBuilder::Cursor(HCURSOR cursor)
{
  extended_class_.hCursor = cursor;
  return *this;
}

WindowBuilder& WindowBuilder::BackgroundColor(HBRUSH color)
{
  extended_class_.hbrBackground = color;
  return *this;
}

WindowBuilder& WindowBuilder::MenuName(LPCSTR menu_name)
{
  extended_class_.lpszMenuName = menu_name;
  return *this;
}

// Window create data
WindowBuilder& WindowBuilder::Style(DWORD style)
{
  create_data_.style = style;
  return *this;
}

WindowBuilder& WindowBuilder::ExtendedStyle(DWORD extended_style)
{
  create_data_.extended_style = extended_style;
  return *this;
}

WindowBuilder& WindowBuilder::Label(LPCSTR label)
{
  create_data_.window_label = label;
  return *this;
}

WindowBuilder& WindowBuilder::PositionX(int x)
{
  create_data_.position_x = x;
  return *this;
}

WindowBuilder& WindowBuilder::PositionY(int y)
{
  create_data_.position_y = y;
  return *this;
}

WindowBuilder& WindowBuilder::Position(int x, int y)
{
  create_data_.position_x = x;
  create_data_.position_y = y;
  return *this;
}

WindowBuilder& WindowBuilder::Width(int width)
{
  create_data_.width = width;
  return *this;
}

WindowBuilder& WindowBuilder::Height(int height)
{
  create_data_.height = height;
  return *this;
}

WindowBuilder& WindowBuilder::Dimension(int width, int height)
{
  create_data_.width = width;
  create_data_.height = height;
  return *this;
}

WindowBuilder& WindowBuilder::ParentWindow(HWND parent_window)
{
  create_data_.parent_window = parent_window;
  return *this;
}

WindowBuilder& WindowBuilder::Menu(HMENU menu)
{
  create_data_.menu = menu;
  return *this;
}

WindowBuilder& WindowBuilder::ExtraParameter(LPVOID extra_parameter)
{
  create_data_.extra_parameter = extra_parameter;
  return *this;
}

// ~~ aff::win32::WindowBuilder
}}
