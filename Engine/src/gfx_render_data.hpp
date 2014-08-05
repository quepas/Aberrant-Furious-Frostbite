#pragma once

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
  RenderData() : model_(nullptr), type_(RenderType::RAW) {}
  RenderData(aff::d3d9::XModel* model) : model_(model), type_(RenderType::X_MODEL) {}

  aff::d3d9::XModel* model_;
  RenderType type_;
};

}}
// ~~ aff::gfx::RenderData
