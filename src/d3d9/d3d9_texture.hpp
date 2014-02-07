#pragma once

#include <d3d9.h>
#include <string>

#include "../util/util_logger.hpp"

namespace aff {
  namespace d3d9 {

class Texture 
{
public:
  Texture(std::string file_path, IDirect3DDevice9* d3d9_device);
  ~Texture();

  inline IDirect3DTexture9* d3d9_texture();
  inline operator IDirect3DTexture9*();
  inline bool IsCorrect();
private:
  IDirect3DTexture9* d3d9_texture_;
  IDirect3DDevice9* d3d9_device_;
  util::Logger logger_;

  // for now...
  Texture(const Texture&);
  Texture& operator=(const Texture&);
};

inline IDirect3DTexture9* Texture::d3d9_texture() {
  return d3d9_texture_;
}

inline Texture::operator IDirect3DTexture9*() {
  return d3d9_texture_;
}

inline bool Texture::IsCorrect() {
  return d3d9_texture_ != nullptr;
}


// ~~ aff::d3d9::Texture
}}
