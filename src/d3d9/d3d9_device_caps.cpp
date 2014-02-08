#include "d3d9_device_caps.hpp"

namespace aff {
  namespace d3d9 {

DeviceCaps::DeviceCaps(IDirect3D9* d3d9_direct)
  : d3d9_direct_(d3d9_direct)
{
}

DeviceCaps::~DeviceCaps()
{
}

const D3DCAPS9& DeviceCaps::GetCaps(
  D3DDEVTYPE device_type, UINT adapter /*= D3DADAPTER_DEFAULT*/) const
{
  D3DCAPS9 device_caps;
  d3d9_direct_->GetDeviceCaps(adapter, device_type, &device_caps);
  return D3DCAPS9(device_caps);
}

const D3DCAPS9& DeviceCaps::GetCapsHAL() const
{
  return GetCaps(D3DDEVTYPE_HAL);
}

const D3DCAPS9& DeviceCaps::GetDeviceCaps(IDirect3DDevice9* d3d9_device)
{
  D3DCAPS9 device_caps;
  d3d9_device->GetDeviceCaps(&device_caps);
  return D3DCAPS9(device_caps);
}

UINT DeviceCaps::GetAdapterCount() const
{
  return d3d9_direct_->GetAdapterCount();
}

UINT DeviceCaps::GetAdapterModeCount(UINT adapter /*= D3DADAPTER_DEFAULT*/) const
{
  return d3d9_direct_->GetAdapterModeCount(adapter, D3DFMT_D16);
}

// ~~ aff::d3d9::DeviceCaps
}}
