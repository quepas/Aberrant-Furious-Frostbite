#pragma once

#include "d3d9_effect.hpp"
#include "d3d9_x_model.hpp"
#include "gfx_render_data.hpp"
#include "gfx_model_3d.hpp"
#include "math_vector3.hpp"

namespace aff {
  namespace core {

class Entity
{
public:
  Entity();
  Entity(const gfx::PureRenderData& pure_render_data);
  Entity(const gfx::RenderData& render_data);
  Entity(d3d9::XModel* model, d3d9::Effect* effect);
  Entity(gfx::Model3d* model, d3d9::Effect* effect);
  virtual ~Entity() {}

  const gfx::PureRenderData& pure_render_data() const { return pure_render_data_; }
  const gfx::RenderData& render_data() const { return render_data_; }
  const math::Vector3f& position() const { return position_; }
  const math::Vector3f& angle_axis() const { return angle_axis_; }

  void MoveTo(math::Vector3f position);
  void MoveBy(math::Vector3f position);
  void RotateBy(math::Vector3f angle_axis);

protected:
  gfx::PureRenderData pure_render_data_;
  gfx::RenderData render_data_;
  math::Vector3f position_;
  math::Vector3f angle_axis_;
};

// ~~ aff::core::Entity
}}
