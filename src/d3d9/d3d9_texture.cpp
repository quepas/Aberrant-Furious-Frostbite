#include "d3d9_texture.hpp"
#include <d3dx9.h>

using std::string;

namespace aff {
  namespace d3d9 {

Texture::Texture(string file_path, IDirect3DDevice9* d3d9_device)
  : d3d9_device_(d3d9_device), 
    d3d9_texture_(nullptr), 
    logger_("d3d9::Texture")
{
  D3DXCreateTextureFromFile(
    d3d9_device_, file_path.c_str(), &d3d9_texture_);
  if (!d3d9_texture_)
    logger_.Error("Loading texture failed: " + file_path);
}

Texture::~Texture()
{
  if (d3d9_texture_)  
    d3d9_texture_->Release();
}

// ~~ aff::d3d9::Texture
}}
