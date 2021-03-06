#pragma once

#include "gfx_pure_render_data.hpp"
#include "math_vector3.hpp"

namespace aff {
  namespace gfx {

enum class Form
{
  BOX,
  PYRAMID
};

class UniformShape
{
public:
  ~UniformShape();
  const PureRenderData& render_data() { return render_data_; }
  static UniformShape Create(Form form);

private:
  UniformShape(PureRenderData render_data);

  static PureRenderData CreateBox();
  static PureRenderData CreatePyramid();
  PureRenderData render_data_;
};

}}
// ~~ aff::gfx::UniformShape
