#pragma once

#include "math_vector3.hpp"

#include <assimp/scene.h>
#include <string>

namespace aff {
  namespace gfx {

class Model3d
{
public:
  Model3d();
  Model3d(const aiScene* scene);
  virtual ~Model3d();

  static Model3d CreateFromFile(std::string file_path);

  unsigned int vertices_number() const { return vertices_number_; }
  const math::Vector3f* const vertices() const { return vertices_; }
  float* const vertices_linear() const { return vertices_linear_; }

protected:
  void InitFromAssimpScene(const aiScene* scene);
  void InitMeshes(aiMesh** meshes, unsigned int size);

  unsigned int vertices_number_;
  math::Vector3f* vertices_;
  float* vertices_linear_; // 3 * vertices_number_
};

}}
// ~~ aff::gfx::Model3d
