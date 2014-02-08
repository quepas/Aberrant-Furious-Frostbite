#pragma once

#pragma warning (disable : 4172)
#include <d3d9.h>

namespace aff {
  namespace d3d9 {

class DeviceCaps
{
public:
  DeviceCaps(IDirect3D9* d3d9_direct);
  ~DeviceCaps();

  const D3DCAPS9& GetCaps(
    D3DDEVTYPE device_type, UINT adapter = D3DADAPTER_DEFAULT) const;
  const D3DCAPS9& GetCapsHAL() const;

  UINT GetAdapterCount() const;
  UINT GetAdapterModeCount(UINT adapter = D3DADAPTER_DEFAULT) const;

  static const D3DCAPS9& GetDeviceCaps(IDirect3DDevice9* d3d9_device);

private:
  IDirect3D9* d3d9_direct_;
};

// ~~ aff::d3d9::DeviceCaps
}}
