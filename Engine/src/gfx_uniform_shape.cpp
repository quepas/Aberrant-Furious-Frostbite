#include "gfx_uniform_shape.hpp"

using aff::math::Vector3f;

namespace aff {
  namespace gfx {

UniformShape::UniformShape(PureRenderData render_data)
  : render_data_(render_data)
{
}

UniformShape::~UniformShape()
{

}

UniformShape UniformShape::Create(Form form)
{
  PureRenderData render_data;
  switch (form)
  {
  case Form::BOX:
    render_data = CreateBox();
    break;
  case Form::PYRAMID:
    render_data = CreatePyramid();
    break;
  }
  return UniformShape(render_data);
}

PureRenderData UniformShape::CreateBox()
{
  static const unsigned int vertices_number = 8;
  static const unsigned int indices_number = 36;

  static Vertex_xyz vertices[vertices_number] = {
    { -1.0f,  1.0f, -1.0f, 0.0f, 0.0f },
    {  1.0f,  1.0f, -1.0f, 0.0f, 0.0f },
    { -1.0f, -1.0f, -1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, 0.0f, 0.0f },
    { -1.0f,  1.0f,  1.0f, 0.0f, 0.0f },
    {  1.0f,  1.0f,  1.0f, 0.0f, 0.0f },
    { -1.0f, -1.0f,  1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f, 0.0f }};

  static short int indices[indices_number] = {
    0, 1, 2,    // side 1
    2, 1, 3,
    4, 0, 6,    // side 2
    6, 0, 2,
    7, 5, 6,    // side 3
    6, 5, 4,
    3, 1, 7,    // side 4
    7, 1, 5,
    4, 5, 0,    // side 5
    0, 5, 1,
    3, 7, 2,    // side 6
    2, 7, 6 };

  static PureRenderData render_data;
  render_data.vertices_number = vertices_number;
  render_data.vertices = vertices;
  render_data.indices_number = indices_number;
  render_data.indices = indices;
  return render_data;
}

PureRenderData UniformShape::CreatePyramid()
{
  static const unsigned int vertices_number = 5;
  static const unsigned int indices_number = 18;

  static Vertex_xyz vertices[vertices_number] = {
    { -3.0f, 0.0f,  3.0f, 0.0f, 0.0f },
    {  3.0f, 0.0f,  3.0f, 0.0f, 0.0f },
    { -3.0f, 0.0f, -3.0f, 0.0f, 0.0f },
    {  3.0f, 0.0f, -3.0f, 0.0f, 0.0f },
    {  0.0f, 2.5f,  0.0f, 0.0f, 0.0f }};

  static short int indices[indices_number] = {
    0, 2, 1,    // base
    1, 2, 3,
    0, 1, 4,    // sides
    1, 3, 4,
    3, 2, 4,
    2, 0, 4};

  static PureRenderData render_data;
  render_data.vertices_number = vertices_number;
  render_data.vertices = vertices;
  render_data.indices_number = indices_number;
  render_data.indices = indices;
  return render_data;
}

}}
// ~~ aff::gfx::UniformShape
