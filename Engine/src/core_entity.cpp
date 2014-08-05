#include "core_entity.hpp"

namespace aff {
  namespace core {

Entity::Entity()
  : position_(0.0f, 0.0f, 0.0f),
    angle_(0.0f)
{

}

Entity::Entity(const gfx::RenderData& render_data)
  : position_(0.0f, 0.0f, 0.0f),
    angle_(0.0f),
    render_data_(render_data)
{

}

Entity::Entity(d3d9::XModel* model, d3d9::Effect* effect)
  : position_(0.0f, 0.0f, 0.0f),
    angle_(0.0f),
    render_data_(model, effect)
{

}

}}
// ~~ aff::core::Entity
