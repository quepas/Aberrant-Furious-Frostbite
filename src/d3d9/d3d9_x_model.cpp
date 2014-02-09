#include "d3d9_x_model.hpp"

#include <string>

using std::string;
using std::to_string;

namespace aff {
  namespace d3d9 {

XModel::XModel(std::string file_path, IDirect3DDevice9* device)
  : mesh_(nullptr),
    logger_("d3d9::XModel")
{
  D3DVERTEXELEMENT9 vertex_decl[] =
  {
    { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, 
      D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, 
      D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
  };

  DWORD material_count;
  ID3DXBuffer* materials_buffer = nullptr;
  if (FAILED(D3DXLoadMeshFromX(
    file_path.c_str(),
    D3DXMESH_MANAGED,
    device,
    NULL,
    &materials_buffer,
    NULL,
    &material_count,
    &mesh_))) 
  {
    logger_.Error("Loading X model failed: " + file_path);
  }
  else
  {      
    logger_.Info("Material count: " + to_string(material_count));
    mesh_->CloneMesh(D3DXMESH_MANAGED, vertex_decl, device, &mesh_);
    D3DXMATERIAL* materials =
      static_cast<D3DXMATERIAL*>(materials_buffer->GetBufferPointer());

    for (DWORD i = 0; i < material_count; ++i) {
      // TODO: fix path to textures
      auto texture_filename = materials[i].pTextureFilename;
      if (texture_filename) {
        auto ptr_texture = new Texture
          (string("resource/model/") + texture_filename, device);
        if (ptr_texture->IsCorrect())
          textures_.push_back(ptr_texture);
      }
      else {
        textures_.push_back(nullptr);
      }
    }    
  }  
  if (materials_buffer)
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
