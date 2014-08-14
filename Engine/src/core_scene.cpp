#include "core_scene.hpp"

#include <algorithm>
#include <cassert>

namespace aff {
  namespace core {

Scene::Scene(Camera* camera)
  : camera_(camera)
{

}

Scene::~Scene()
{

}

void Scene::InsertEntity(Entity* entity)
{
  assert(entity != nullptr);
  entities_.push_back(entity);
}

void Scene::DeleteEntity(Entity*& entity)
{
  assert(entity != nullptr);
  auto idx = std::find(entities_.begin(), entities_.end(), entity);
  if (idx != entities_.end()) {
    entities_.erase(idx);
    delete entity;
    entity = nullptr;
  }
}

void Scene::SetCamera(Camera* camera)
{
  assert(camera != nullptr);
  camera_ = camera;
}

void Scene::SetSkybox(Skybox* skybox)
{
  assert(skybox != nullptr);
  skybox_ = skybox;
}

}}
// ~~ aff::core::Scene
