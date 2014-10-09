#pragma once

#include "core_camera.hpp"
#include "core_entity.hpp"
#include "core_skybox.hpp"

#include <vector>

namespace aff {
  namespace core {

class Scene
{
public:
  Scene(Camera* camera);
  ~Scene();

  void SetCamera(Camera* camera);
  void SetSkybox(Skybox* skybox);

  void InsertEntity(Entity* entity);
  void DeleteEntity(Entity*& entity);

  Camera* camera() { return camera_; }
  Camera* camera() const { return camera_; }
  const std::vector<Entity*>& entities() const { return entities_; }
  const Skybox* skybox() const { return skybox_; }

protected:
  Camera* camera_;
  std::vector<Entity*> entities_;
  Skybox* skybox_;
private:
};

}}
// ~~ aff::core::Scene
