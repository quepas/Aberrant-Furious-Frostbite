#include "core_entity.hpp"

namespace aff {
  namespace core {

Entity::Entity()
  : position_(0.0f, 0.0f, 0.0f),
    angle_(0.0f)
{

}

Entity::Entity(d3d9::XModel* model)
  : position_(0.0f, 0.0f, 0.0f),
    angle_(0.0f)
{
  render_data_.model_ = model;
}

}}
// ~~ aff::core::Entity
