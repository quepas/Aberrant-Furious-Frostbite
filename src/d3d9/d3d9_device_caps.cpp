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

const D3DCAPS9& DeviceCaps::GetCaps
  (D3DDEVTYPE device_type, UINT adapter /*= D3DADAPTER_DEFAULT*/) const
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

const D3DDISPLAYMODE& DeviceCaps::GetAdapterDisplayMode
  (UINT adapter /*= D3DADAPTER_DEFAULT*/) const
{
  D3DDISPLAYMODE display_mode;
  d3d9_direct_->GetAdapterDisplayMode(adapter, &display_mode);
  return D3DDISPLAYMODE(display_mode);
}

const D3DADAPTER_IDENTIFIER9& DeviceCaps::GetAdapterIdentifier
  (UINT adapter /*= D3DADAPTER_DEFAULT*/) const
{
  D3DADAPTER_IDENTIFIER9 adapter_identifier;
  d3d9_direct_->GetAdapterIdentifier(adapter, 0, &adapter_identifier);
  return D3DADAPTER_IDENTIFIER9(adapter_identifier);
}

// ~~ aff::d3d9::DeviceCaps
}}
