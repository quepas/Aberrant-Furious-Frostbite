#include "d3d9_renderer.hpp"
#include "math_util.hpp"
#include "gfx_pure_render_data.hpp"

#include <cassert>

using aff::core::Camera;
using aff::core::Entity;
using aff::gfx::RenderType;
using aff::gfx::PureRenderData;
using aff::gfx::VERTEX_XYZ_FVF;
using aff::gfx::Vertex_xyz;
using aff::math::ToD3DXVector3;
using std::string;

namespace aff {
  namespace d3d9 {

Renderer::Renderer(D3DPRESENT_PARAMETERS present_parameters, HWND hwnd)
  : present_parameters_(present_parameters),
    hwnd_(hwnd),
    direct_(nullptr),
    device_(nullptr)
{
  D3DXMatrixIdentity(&view_);
  D3DXMatrixIdentity(&projection_);
}

Renderer::~Renderer()
{
}

void Renderer::Initialize()
{
  direct_ = Direct3DCreate9(D3D_SDK_VERSION);
  if (FAILED(direct_->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    hwnd_,
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &present_parameters_,
    &device_)))
  {
    //logger.Fatal("Direct3D device is null");
  }
  storage_ = new RenderStorage(device_);

  device_->SetRenderState(D3DRS_ZENABLE, true);
  device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void Renderer::Release()
{
  device_->Release();
  direct_->Release();
}

bool Renderer::IsCorrect()
{
  return device_ != nullptr && direct_ != nullptr;
}

void Renderer::BeforeRendering()
{
  device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff00ff00, 1, 0);
  device_->BeginScene();
}

void Renderer::AfterRendering()
{
  device_->EndScene();
  device_->Present(NULL, NULL, NULL, NULL);
}

void Renderer::RenderXModel(const XModel& model, const Effect& effect, const D3DXMATRIX& model_matrix)
{
  assert(model.IsCorrect());
  assert(effect.IsCorrect());

  D3DXMATRIX full_matrix = model_matrix * view_ * projection_;

  const auto& effect_data = effect.d3d9_effect();
  effect_data->SetMatrix
    ("matrix_world_view_proj", &full_matrix);

  UINT passes;
  D3DXHANDLE tech;
  effect_data->FindNextValidTechnique(0, &tech);
  effect_data->SetTechnique(tech);
  effect_data->Begin(&passes, 0);
  for (UINT pass = 0; pass < passes; ++pass)
  {
    effect_data->BeginPass(pass);

    const auto& materials = model.textures();
    for (UINT i = 0; i < model.subset_number(); ++i) {
      if (i < materials.size())
        effect_data->SetTexture("tex0", materials[i]->d3d9_texture());
      effect_data->CommitChanges();
      model.mesh()->DrawSubset(i);
    }

    effect_data->EndPass();
  }
  effect_data->End();
}

void Renderer::RenderRawModel(const gfx::Model3d& model, const Effect& effect, const D3DXMATRIX& model_matrix)
{
  assert(effect.IsCorrect());

  for (auto& data : model.render_data()) {
    D3DXMATRIX full_matrix = model_matrix * view_ * projection_;

    const auto& effect_data = effect.d3d9_effect();
    effect_data->SetMatrix
      ("matrix_world_view_proj", &full_matrix);

    UINT passes;
    D3DXHANDLE tech;
    effect_data->FindNextValidTechnique(0, &tech);
    effect_data->SetTechnique(tech);
    effect_data->Begin(&passes, 0);
    for (UINT pass = 0; pass < passes; ++pass)
    {
      effect_data->BeginPass(pass);

      effect_data->SetTexture("tex0", storage_->FetchTexture(data));
      effect_data->CommitChanges();
      device_->SetFVF(VERTEX_XYZ_FVF);
      device_->SetStreamSource(0, storage_->FetchVertexBuffer(data), 0, sizeof(Vertex_xyz));
      device_->SetIndices(storage_->FetchIndexBuffer(data));
      device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, data.vertices_number, 0, data.faces_number);
      effect_data->EndPass();
    }
    effect_data->End();
  }
}

void Renderer::RenderEntity(const Entity& entity)
{  
  auto render_data = entity.render_data();
  auto render_type = render_data.type_;

  D3DXMATRIX entity_matrix = PrepareEntityMatrix(entity);
  switch (render_type)
  {
  case RenderType::X_MODEL:
    RenderXModel(*render_data.model_x_, *render_data.effect_, entity_matrix);
    break;
  case RenderType::RAW:
    RenderRawModel(*render_data.model_raw_, *render_data.effect_, entity_matrix);
    break;
  default:
    break;
  }
}

void Renderer::SetCurrentCamera(const Camera& camera)
{
  D3DXMatrixPerspectiveFovLH(
    &projection_,
    D3DXToRadian(camera.field_of_view()),
    camera.view_ratio(),
    camera.near_clipping_plane(),
    camera.far_clipping_plane());
  D3DXMatrixLookAtLH(
    &view_,
    &ToD3DXVector3(camera.position()),
    &ToD3DXVector3(camera.look_at()),
    &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

D3DXMATRIX Renderer::PrepareEntityMatrix(const Entity& entity)
{
  D3DXMATRIX translation;
  D3DXMATRIX rotation;
  auto position = entity.position();
  D3DXMatrixTranslation(&translation, position.x, position.y, position.z);
  auto angle_axis = entity.angle_axis();
  D3DXMatrixRotationYawPitchRoll(&rotation, angle_axis.x, angle_axis.y, angle_axis.z);
  return rotation * translation;
}

void Renderer::TrackEntity(const core::Entity& entity)
{
  // TODO: whoooo! change this chain mister Quepas... quickly :)
  auto render_parts = entity.render_data().model_raw_->render_data();
  for (auto& data : render_parts) {
    storage_->Push(data);
  }
}

}}
// ~~ aff::d3d9::Renderer
