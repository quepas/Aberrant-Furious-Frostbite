#pragma once

#include <Windows.h>

namespace aff {
  namespace win32 {

class Input
{
public:
  Input();
  ~Input();

  static bool IsKeyPressed(int key_code);

  bool RetriveInput(const MSG& msg);

  inline const POINT& mouse_current() const;
  inline const POINT& mouse_last() const;
  inline const POINT& mouse_diff() const;
private:
  struct MouseData
  {
    POINT current;
    POINT last;
    POINT diff;
  };

  MouseData mouse_;
};

inline const POINT& Input::mouse_current() const {
  return mouse_.current;
}

inline const POINT& Input::mouse_last() const {
  return mouse_.last;
}

inline const POINT& Input::mouse_diff() const {
  return mouse_.diff;
}

// ~~ aff::win32::Input
}}
