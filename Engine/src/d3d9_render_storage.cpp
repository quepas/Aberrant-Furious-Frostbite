#include "d3d9_render_storage.hpp"
#include "d3d9_texture.hpp"

#include <cassert>
#include <string>

using aff::gfx::PureHash;
using aff::gfx::Vertex_xyz;
using aff::gfx::VERTEX_XYZ_FVF;
using std::make_pair;
using std::size_t;
using std::string;

namespace aff {
  namespace d3d9 {

RenderStorage::RenderStorage(IDirect3DDevice9* device)
  : device_(device)
{
  assert(device_ != nullptr);
}

RenderStorage::~RenderStorage()
{

}

void RenderStorage::Push(const gfx::PureRenderData& data)
{
  if (!InStorage(data)) {
    size_t hash = PureHash()(data);
    IDirect3DVertexBuffer9* vertex_buffer = nullptr;
    size_t vertices_size = data.vertices_number * sizeof(Vertex_xyz);

    device_->CreateVertexBuffer(
      vertices_size,
      0,
      VERTEX_XYZ_FVF,
      D3DPOOL_DEFAULT,
      &vertex_buffer,
      0);
    void* vdata;
    vertex_buffer->Lock(0, vertices_size, (void**) &vdata, D3DLOCK_DISCARD);
    memcpy(vdata, (void*) data.vertices, vertices_size);
    vertex_buffer->Unlock();

    IDirect3DIndexBuffer9* index_buffer = nullptr;
    size_t indices_size = data.indices_number * sizeof(short int);
    device_->CreateIndexBuffer(
      indices_size,
      0,
      D3DFMT_INDEX16,
      D3DPOOL_MANAGED,
      &index_buffer,
      nullptr);
    void* idata;
    index_buffer->Lock(0, 0, (void**) &idata, 0);
    memcpy(idata, data.indices, indices_size);
    index_buffer->Unlock();

    IDirect3DTexture9* texture;
    D3DXCreateTextureFromFile(device_, data.texture_name.c_str(), &texture);

    // pushing data
    vertex_buffers_.insert(make_pair(hash, vertex_buffer));
    index_buffers_.insert(make_pair(hash, index_buffer));
    textures_.insert(make_pair(hash, texture));
  }
}

void RenderStorage::Release(const gfx::PureRenderData& data)
{
  size_t hash = PureHash()(data);
  assert(vertex_buffers_[hash] != nullptr);
  vertex_buffers_[hash]->Release();
  assert(index_buffers_[hash] != nullptr);
  index_buffers_[hash]->Release();
  assert(textures_[hash] != nullptr);
  textures_[hash]->Release();
}

bool RenderStorage::InStorage(const gfx::PureRenderData& data) const
{
  size_t hash = PureHash()(data);
  return vertex_buffers_.find(hash) != vertex_buffers_.end()
    && index_buffers_.find(hash) != index_buffers_.end()
    && textures_.find(hash) != textures_.end();
}

IDirect3DVertexBuffer9* RenderStorage::FetchVertexBuffer(const gfx::PureRenderData& data)
{
  size_t hash = PureHash()(data);
  assert(vertex_buffers_[hash] != nullptr);
  return vertex_buffers_[hash];
}

IDirect3DIndexBuffer9* RenderStorage::FetchIndexBuffer(const gfx::PureRenderData& data)
{
  size_t hash = PureHash()(data);
  assert(index_buffers_[hash] != nullptr);
  return index_buffers_[hash];
}

IDirect3DTexture9* RenderStorage::FetchTexture(const gfx::PureRenderData& data)
{
  size_t hash = PureHash()(data);
  assert(textures_[hash] != nullptr);
  return textures_[hash];
}

}}
// ~~ aff::d3d9::RenderStorage
