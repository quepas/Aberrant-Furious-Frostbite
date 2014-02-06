#include "win32_window.hpp"

#include "../util/util_random.hpp"

namespace aff {
  namespace win32 {

LRESULT CALLBACK DefualtWndProc(
  HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT paint_struct;
  switch (message)
  {
  case WM_CREATE:
    return 0;  
  case WM_DESTROY:
  case WM_CLOSE:
    PostQuitMessage(0);
    return 0;
  case WM_PAINT:
    BeginPaint(hWND, &paint_struct);
    EndPaint(hWND, &paint_struct);
    return 0;
  default:
    return DefWindowProc(hWND, message, wParam, lParam);
  }
}

Window::Window(WNDCLASSEX& extended_class, CreateData& create_data)
  : extended_class_(extended_class),
    create_data_(create_data),
    hwnd_(NULL)
{
}

Window::~Window()
{
}

HWND Window::Create()
{
  if (!RegisterClassEx(&extended_class_))
    return NULL;

  hwnd_ = CreateWindowEx(
    create_data_.extended_style, 
    extended_class_.lpszClassName, 
    create_data_.window_label, 
    create_data_.style, 
    create_data_.position_x, 
    create_data_.position_y,
    create_data_.width,
    create_data_.height,
    create_data_.parent_window, 
    create_data_.menu, 
    extended_class_.hInstance, 
    create_data_.extra_parameter);
  return hwnd_;
}

HWND Window::CreateAndShow()
{
  Create();
  if (!hwnd_) {
    ShowWindow(hwnd_, SW_SHOW);
    UpdateWindow(hwnd_);
  }
  return hwnd_;
}

void Window::DefaultWndClassEx(WNDCLASSEX& wnd_class_ex)
{  
  wnd_class_ex.cbSize = sizeof(WNDCLASSEX);
  wnd_class_ex.style = CS_HREDRAW | CS_VREDRAW;
  wnd_class_ex.lpfnWndProc = DefualtWndProc;
  wnd_class_ex.cbClsExtra = 0;
  wnd_class_ex.cbWndExtra = 0;
  wnd_class_ex.hInstance = GetModuleHandle(NULL);
  wnd_class_ex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wnd_class_ex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wnd_class_ex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wnd_class_ex.hbrBackground = NULL;
  wnd_class_ex.lpszMenuName = NULL;
  wnd_class_ex.lpszClassName = util::random::Generate32Chars().c_str();
}

void Window::DefaultWndCreateData(CreateData& create_data)
{
  create_data.style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
  create_data.height = 300;
  create_data.width = 400;
  create_data.position_x = 0;
  create_data.position_y = 0;
  create_data.window_label = "Default Window Name";
  create_data.extended_style = NULL;
  create_data.extra_parameter = NULL;
  create_data.parent_window = NULL;
  create_data.menu = NULL;
}
// ~~ aff::win32::Window
}}
