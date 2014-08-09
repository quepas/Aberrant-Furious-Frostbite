#include "gfx_model_3d.hpp"

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

using aff::util::Logger;
using Assimp::Importer;
using std::string;
using std::to_string;

namespace aff {
  namespace gfx {

util::Logger Model3d::logger_("Model3d");

Model3d::Model3d()
{

}

Model3d::Model3d(const aiScene* scene)
{
  InitFromAssimpScene(scene);
}

Model3d::~Model3d()
{

}

Model3d Model3d::CreateFromFile(const std::string& file_path)
{
  Importer model_importer;
  const aiScene* scene = model_importer
    .ReadFile(
      file_path,
      aiProcessPreset_TargetRealtime_MaxQuality |
      // DirectX has left handed coordinate system
      // TODO: move any dx dependency from gfx package
      aiProcess_ConvertToLeftHanded); 

  if (!scene) {
    logger_.Error(string("Assimp failed: ") + model_importer.GetErrorString());
    return Model3d();
  }
  else {
    logger_.Info(Model3d::QuickInfo(scene));
    return Model3d(scene);
  }
}

void Model3d::InitFromAssimpScene(const aiScene* scene)
{
  aiMesh** meshes = scene->mMeshes;
  aiMaterial** materials = scene->mMaterials;

  if (scene->HasMeshes()) {
    unsigned int global_idx = 0;
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
      PureRenderData render_part;
      aiMesh* mesh = meshes[i];

      if (mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE) {
        aiVector3D* verts = mesh->mVertices;
        aiVector3D* uvs = mesh->mTextureCoords[0];
        unsigned int num_vertices = mesh->mNumVertices;
        render_part.vertices_number = num_vertices;
        render_part.vertices = new Vertex_xyz[num_vertices];
        unsigned int num_faces = mesh->mNumFaces;
        render_part.faces_number = num_faces;
        render_part.indices = new short int[num_faces * 3];
        render_part.indices_number = num_faces * 3;
        aiFace* faces = mesh->mFaces;

        for (unsigned int j = 0; j < num_vertices; ++j) {
          auto point = verts[j];
          auto uv = uvs[j];
          Vertex_xyz vertex_xyz;
          vertex_xyz.x = point.x;
          vertex_xyz.y = point.y;
          vertex_xyz.z = point.z;
          vertex_xyz.u = uv.x;
          vertex_xyz.v = uv.y;
          render_part.vertices[j] = vertex_xyz;
        }

        for (unsigned int f_idx = 0; f_idx < num_faces; ++f_idx) {
          auto face = faces[f_idx];
          unsigned int indices_idx = f_idx * 3;
          render_part.indices[indices_idx] = face.mIndices[0];
          render_part.indices[indices_idx + 1] = face.mIndices[1];
          render_part.indices[indices_idx + 2] = face.mIndices[2];
        }

        // load texture name from material
        if (scene->HasMaterials()) {
          auto material_idx = mesh->mMaterialIndex;
          auto material = materials[material_idx];
          aiString texture_name;
          material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_name);
          render_part.texture_name = texture_name.data;
        }
      }
      else {
        logger_.Error("Model hasn't got triangle faces");
      }
      render_parts_.push_back(render_part);
    }
  }
}

string Model3d::QuickInfo(const aiScene* scene)
{
  string info;
  info += "\n----------------------------------------";
  info += "\n\tNumber of textures: ";
  info += to_string(scene->mNumTextures);
  info += "\n\tNumber of materials: ";
  info += to_string(scene->mNumMaterials);
  info += "\n----------------------------------------";
  return info;
}

bool Model3d::IsCorrect() const
{
  return !render_parts_.empty();
}

}}
// ~~ aff::gfx::Model3d
