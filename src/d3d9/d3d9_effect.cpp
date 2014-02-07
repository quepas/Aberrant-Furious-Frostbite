#include "d3d9_effect.hpp"

using std::string;

namespace aff {
  namespace d3d9 {

Effect::Effect(string file_path, IDirect3DDevice9* d3d9_device)
  : d3d9_device_(d3d9_device),
    d3d9_effect_(nullptr),
    logger_("d3d9::Effect")
{
  ID3DXBuffer* error_buffer;
  D3DXCreateEffectFromFile(
    d3d9_device_, file_path.c_str(), NULL, 
    NULL, 0, NULL, &d3d9_effect_, &error_buffer);
  if (!d3d9_effect_)   
    logger_.Error("Loading shader failed: " + file_path);
  if (error_buffer)
    logger_.Error(string("\tLoading errors: ")
      + static_cast<char*>(error_buffer->GetBufferPointer()));  
}

Effect::~Effect()
{
  if (d3d9_effect_)
    d3d9_effect_->Release();
}

// ~~ aff::d3d9::Effect
}}
