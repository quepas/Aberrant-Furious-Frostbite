#pragma once

#include "d3d9_effect.hpp"
#include "d3d9_x_model.hpp"

namespace aff {
  namespace gfx {

enum class RenderType
{
  RAW,
  X_MODEL
};

struct RenderData
{
  RenderData() : model_(nullptr), effect_(nullptr), type_(RenderType::RAW) {}
  RenderData(d3d9::XModel* model, d3d9::Effect* effect)
    : model_(model), effect_(effect), type_(RenderType::X_MODEL) {}

  d3d9::XModel* model_;
  d3d9::Effect* effect_;
  RenderType type_;
};

}}
// ~~ aff::gfx::RenderData
