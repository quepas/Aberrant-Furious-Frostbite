#pragma once

#include "d3d9_x_model.hpp"
#include "gfx_render_data.hpp"
#include "math_vector3.hpp"

namespace aff {
  namespace core {

class Entity
{
public:
  Entity();
  Entity(d3d9::XModel* model);
  virtual ~Entity() {}

  const gfx::RenderData& render_data() const { return render_data_; }
  const math::Vector3f& position() const { return position_; }
  float angle() const { return angle_; }

protected:
  gfx::RenderData render_data_;
  math::Vector3f position_;
  float angle_;

};

// ~~ aff::core::Entity
}}
