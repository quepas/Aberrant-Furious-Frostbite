#pragma once

#include <string>
#include <vector>
#include <d3dx9.h>

#include "d3d9_texture.hpp"
#include "../util/util_logger.hpp"

namespace aff {
  namespace d3d9 {

class XModel
{
public:
  XModel(std::string file_path, IDirect3DDevice9* d3d9_device);
  ~XModel();

  inline ID3DXMesh* mesh() const;  
  inline const std::vector<Texture*>& textures() const;
  
  inline bool IsCorrect() const;
private:
  ID3DXMesh* mesh_;
  std::vector<Texture*> textures_;  

  // for now...
  XModel(const XModel&);
  XModel& operator=(const XModel&);
};

inline ID3DXMesh* XModel::mesh() const {
  return mesh_;
}

inline const std::vector<Texture*>& XModel::textures() const {
  return textures_;
}

inline bool XModel::IsCorrect() const {
  return false;
}

// ~~ aff::d3d9::XModel
}}
