#pragma once

#include <d3d9.h>
#include <string>
#include <functional>

namespace aff {
  namespace gfx {

const DWORD VERTEX_XYZ_FVF = D3DFVF_XYZ | D3DFVF_TEX1;

struct Vertex_xyz 
{
  float x, y, z;
  float u, v;
};

template<typename T>
struct Data
{
  T* buffer;
  unsigned int size;
};

typedef Data<Vertex_xyz> VerticesData;
typedef Data<short int> IndicesData;

struct PureRenderData
{
public:
  PureRenderData() : version(1) {}

  Vertex_xyz* vertices;
  unsigned int vertices_number;
  unsigned int faces_number;
  short int* indices;
  unsigned int indices_number;
  std::string texture_name;
  std::string effect_name;

  std::size_t texture_id;
  std::size_t effect_id;

  void IncreaseVersion() { ++version; }
  const std::size_t CheckVersion() const { return version; }

private:
  std::size_t version; // every change in data increment this !
};

template <typename T>
class PureRenderDataHash;

template<>
class PureRenderDataHash < PureRenderData >
{
public:
  std::size_t operator()(const PureRenderData& data) const
  {
    std::size_t hash0 = std::hash<std::size_t>()(data.CheckVersion());
    std::size_t hash1 = std::hash<Vertex_xyz*>()(data.vertices);
    std::size_t hash2 = std::hash<unsigned int>()(data.vertices_number);
    std::size_t hash3 = std::hash<unsigned int>()(data.faces_number);
    std::size_t hash4 = std::hash<short int*>()(data.indices);
    std::size_t hash5 = std::hash<unsigned int>()(data.indices_number);
    std::size_t hash6 = std::hash<std::string>()(data.texture_name);
    return hash0 ^ hash1 ^ (hash2 << 1) ^ (hash3 << 2) ^ (hash4 << 3) ^ (hash5 << 4) ^ (hash6 << 5);
  }
};

typedef PureRenderDataHash<PureRenderData> PureHash;

}}
// ~~ aff::gfx::PureRenderData
