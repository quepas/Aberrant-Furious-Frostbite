#pragma once

#include "d3d9_effect.hpp"
#include "d3d9_x_model.hpp"
#include "gfx_model_3d.hpp"

#include <string>

namespace aff {
  namespace gfx {

enum class RenderType
{
  RAW,
  X_MODEL,
  NONE
};

struct RenderData
{
  RenderData() : type_(RenderType::NONE) {}
  RenderData(gfx::Model3d* model, d3d9::Effect* effect) 
    : model_raw_(model), effect_(effect), type_(RenderType::RAW) {}
  RenderData(d3d9::XModel* model, d3d9::Effect* effect)
    : model_x_(model), effect_(effect), type_(RenderType::X_MODEL) {}

  d3d9::XModel* model_x_;
  d3d9::Effect* effect_;
  gfx::Model3d* model_raw_;
  RenderType type_;
};

}}
// ~~ aff::gfx::RenderData
