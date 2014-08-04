#pragma once

namespace aff {
  namespace gfx {

class Renderer
{
public:
  virtual void Initialize() = 0;
  virtual void Release() = 0;
  virtual bool IsCorrect() = 0;

  virtual void BeforeRendering() = 0;
  virtual void AfterRendering() = 0;
protected:

private:
};

}}
// ~~ aff::gfx::Renderer
