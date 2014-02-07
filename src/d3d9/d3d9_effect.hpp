#pragma once

#include <d3dx9.h>
#include <string>

#include "../util/util_logger.hpp"

namespace aff {
  namespace d3d9 {

class Effect
{
public:
  Effect(std::string file_path, IDirect3DDevice9* d3d9_device);
  ~Effect();

  inline ID3DXEffect* d3d9_effect();
  inline operator ID3DXEffect*();
  inline bool IsCorrect();
private:
  ID3DXEffect* d3d9_effect_;
  IDirect3DDevice9* d3d9_device_;
  util::Logger logger_;

  // for now...
  Effect(const Effect&);
  Effect& operator=(const Effect&);
};

inline ID3DXEffect* Effect::d3d9_effect() {
  return d3d9_effect_;
}

inline Effect::operator ID3DXEffect*() {
  return d3d9_effect_;
}

inline bool Effect::IsCorrect() {
  return d3d9_effect_ != nullptr;
}

// ~~ aff::d3d9::Effect
}}
