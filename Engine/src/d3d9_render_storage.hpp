#pragma once

#include "gfx_pure_render_data.hpp"

#include <d3dx9.h>
#include <map>

namespace aff {
  namespace d3d9 {

class RenderStorage
{
public:
  RenderStorage(IDirect3DDevice9* device);
  ~RenderStorage();

  void Push(const gfx::PureRenderData& data);
  void Release(const gfx::PureRenderData& data);
  bool InStorage(const gfx::PureRenderData& data) const;

  IDirect3DVertexBuffer9* FetchVertexBuffer(const gfx::PureRenderData& data);
  IDirect3DIndexBuffer9* FetchIndexBuffer(const gfx::PureRenderData& data);
  IDirect3DTexture9* FetchTexture(const gfx::PureRenderData& data);

  RenderStorage(const RenderStorage&) = delete;
  RenderStorage& operator=(const RenderStorage&) = delete;

private:
  std::map<std::size_t, IDirect3DVertexBuffer9*> vertex_buffers_;
  std::map<std::size_t, IDirect3DIndexBuffer9*> index_buffers_;
  std::map<std::size_t, IDirect3DTexture9*> textures_;

  IDirect3DDevice9* device_;
};

}}
// ~~ aff::d3d9::RenderStorage
