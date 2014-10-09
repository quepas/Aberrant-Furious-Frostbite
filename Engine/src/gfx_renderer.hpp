#pragma once

#include "core_camera.hpp"
#include "core_entity.hpp"

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

  virtual void RenderEntity(const core::Entity& entity) = 0;
  virtual void SetCurrentCamera(core::Camera* camera) = 0;
protected:

private:
};

}}
// ~~ aff::gfx::Renderer
