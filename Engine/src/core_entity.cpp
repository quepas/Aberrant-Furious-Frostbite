#include "core_entity.hpp"

namespace aff {
  namespace core {

Entity::Entity()
  : position_(0.0f, 0.0f, 0.0f),
    angle_axis_(0.0f, 0.0f, 0.0f)
{

}

Entity::Entity(const gfx::RenderData& render_data)
  : position_(0.0f, 0.0f, 0.0f),
    angle_axis_(0.0f, 0.0f, 0.0f),
    render_data_(render_data)
{

}

Entity::Entity(d3d9::XModel* model, d3d9::Effect* effect)
  : position_(0.0f, 0.0f, 0.0f),
    angle_axis_(0.0f, 0.0f, 0.0f),
    render_data_(model, effect)
{

}

Entity::Entity(gfx::Model3d* model, d3d9::Effect* effect)
  : position_(0.0f, 0.0f, 0.0f),
    angle_axis_(0.0f, 0.0f, 0.0f),
    render_data_(model, effect)
{

}

Entity::Entity(const gfx::PureRenderData& pure_render_data)
  : position_(0.0f, 0.0f, 0.0f),
    angle_axis_(0.0f, 0.0f, 0.0f),
    pure_render_data_(pure_render_data)
{

}

void Entity::MoveTo(math::Vector3f position)
{
  position_ = position;
}

void Entity::MoveBy(math::Vector3f position)
{
  position_ += position;
}

void Entity::RotateBy(math::Vector3f angle_axis)
{
  angle_axis_ += angle_axis;
}

}}
// ~~ aff::core::Entity
