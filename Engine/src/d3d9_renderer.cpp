#include "d3d9_renderer.hpp"
#include "d3d9_camera.hpp"
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
  storage_->LoadDefaultData();

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
  device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1, 0);
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

void Renderer::SetCurrentCamera(const core::Camera& camera)
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

void Renderer::SetCurrentCamera(d3d9::Camera& camera)
{
  camera.Update();
  view_ = camera.view_matrix();
  projection_ = camera.projection_matrix();
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
  auto model = entity.render_data().model_raw_;
  if (model != nullptr) {
    auto render_parts = model->render_data();
    for (auto& data : render_parts) {
      storage_->Push(data);
    }
  }
  else {
    storage_->Push(entity.pure_render_data());
  }
}

void Renderer::RenderScene(const core::Scene& scene)
{
  SetCurrentCamera(*scene.camera());
  for (auto& entity : scene.entities()) {
    RenderEntity(*entity);
  }
}

void Renderer::TrackScene(const core::Scene& scene)
{
  SetCurrentCamera(*scene.camera());
  for (auto& entity : scene.entities()) {
    TrackEntity(*entity);
  }
}

void Renderer::RenderEntity2(const core::Entity& entity, const Effect& effect)
{
  auto& render_data = entity.pure_render_data();
  D3DXMATRIX entity_matrix = PrepareEntityMatrix(entity);
  D3DXMATRIX scale;
  D3DXMatrixScaling(&scale, 0.25, 0.25, 0.25);
  D3DXMATRIX full_matrix = scale * entity_matrix * view_ * projection_;

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

    //if (!render_data.texture_name.empty()) {
      effect_data->SetTexture("tex0", storage_->FetchTexture(render_data));
    //}
    effect_data->CommitChanges();
    device_->SetFVF(VERTEX_XYZ_FVF);
    device_->SetStreamSource(0, storage_->FetchVertexBuffer(render_data), 0, sizeof(Vertex_xyz));
    device_->SetIndices(storage_->FetchIndexBuffer(render_data));
    device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, render_data.vertices_number, 0, render_data.faces_number);
    effect_data->EndPass();
  }
  effect_data->End();
}

void Renderer::RenderMesh(ID3DXMesh& mesh, const d3d9::Texture& texture)
{
  /*D3DXInitMa(mtrl, 1.0f, 0.5f, 0.5f, 0.6f);
  m_pd3dDevice->SetMaterial(&mtrl);*/
 device_->SetTexture(1, texture.d3d9_texture());
  D3DXMATRIX matrix;
  D3DXMatrixTranslation(&matrix, 0.0f, 0.0f, 0.0f);
  device_->SetTransform(D3DTS_WORLD, &matrix);
  mesh.DrawSubset(0);
}

}}
// ~~ aff::d3d9::Renderer
