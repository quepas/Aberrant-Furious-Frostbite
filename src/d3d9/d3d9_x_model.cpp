#include "d3d9_x_model.hpp"

namespace aff {
  namespace d3d9 {

XModel::XModel(std::string file_path, IDirect3DDevice9* d3d9_device)
  : mesh_(nullptr)
{
  D3DVERTEXELEMENT9 vertex_decl[] =
  {
    { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
  };

  DWORD material_count;
  ID3DXBuffer* materials_buffer;
  D3DXLoadMeshFromX(
    file_path.c_str(), 
    D3DXMESH_MANAGED, 
    d3d9_device, 
    NULL, 
    &materials_buffer, 
    NULL, 
    &material_count,
    &mesh_);
  mesh_->CloneMesh(D3DXMESH_MANAGED, vertex_decl, d3d9_device, &mesh_);
  D3DXMATERIAL* materials = 
    static_cast<D3DXMATERIAL*>(materials_buffer->GetBufferPointer());

  for (DWORD i = 0; i < material_count; ++i) {
    auto ptr_texture = new Texture(materials[i].pTextureFilename, d3d9_device);
    if (ptr_texture->IsCorrect())
      textures_.push_back(ptr_texture);
  }
  materials_buffer->Release();
}

XModel::~XModel()
{
  if (mesh_)
    mesh_->Release();
  for (Texture*& texture_ptr : textures_) {
    delete texture_ptr;
  }
  textures_.clear();
}

// ~~ aff::d3d9::XModel    
}}
