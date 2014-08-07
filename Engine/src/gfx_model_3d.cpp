#include "gfx_model_3d.hpp"
#include "util_logger.hpp"

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <string>

using aff::math::Vector3f;
using aff::util::Logger;
using Assimp::Importer;
using std::string;

namespace aff {
  namespace gfx {

Model3d::Model3d()
{

}

Model3d::Model3d(const aiScene* scene)
{

}

Model3d::~Model3d()
{

}

Model3d Model3d::CreateFromFile(std::string file_path)
{
  Logger logger("");
  Importer model_importer;
  const aiScene* scene = model_importer
    .ReadFile(file_path, aiProcessPreset_TargetRealtime_Fast);

  if (!scene) {
    logger.Error(string("Assimp failed: ") + model_importer.GetErrorString());
    return Model3d();
  }
  else {
    return Model3d(scene);
  }
}

void Model3d::InitFromAssimpScene(const aiScene* scene)
{
  if (scene->HasMeshes()) {
    InitMeshes(scene->mMeshes, scene->mNumMeshes);
  }
}

void Model3d::InitMeshes(aiMesh** meshes, unsigned int size)
{
  //for (unsigned int i = 0; i < size; ++i) {
    auto mesh = meshes[0];
    auto vertices = mesh->mVertices;
    vertices_number_ = mesh->mNumVertices;
    vertices_ = new Vector3f[vertices_number_];
    vertices_linear_ = new float[vertices_number_ * 3];

    unsigned int linear_index = 0;
    for (unsigned int j = 0; j < vertices_number_; ++j) {
      auto point = vertices[j];

      // vectorized
      Vector3f point_vec(point.x, point.y, point.z);
      vertices_[j] = point_vec;

      // linear
      vertices_linear_[linear_index] = point.x;
      vertices_linear_[linear_index+1] = point.y;
      vertices_linear_[linear_index+2] = point.z;
      linear_index += 3;
    }
  //}
}

}}
// ~~ aff::gfx::Model3d
