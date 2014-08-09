#pragma once

#include <d3d9.h>
#include <string>

namespace aff {
  namespace gfx {

const DWORD VERTEX_XYZ_FVF = D3DFVF_XYZ | D3DFVF_TEX1;

struct Vertex_xyz 
{
  float x, y, z;
  float u, v;
};

struct PureRenderData
{
  Vertex_xyz* vertices;
  unsigned int vertices_number;
  unsigned int faces_number;
  short int* indices;
  unsigned int indices_number;
  std::string texture_name;
};

}}
// ~~ aff::gfx::PureRenderData
