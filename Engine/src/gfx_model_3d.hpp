#pragma once

#include "gfx_pure_render_data.hpp"
#include "util_logger.hpp"

#include <assimp/scene.h>
#include <string>
#include <vector>

namespace aff {
  namespace gfx {

class Model3d
{
public:
  Model3d();
  Model3d(const aiScene* scene);
  virtual ~Model3d();

  static Model3d CreateFromFile(const std::string& file_path);
  static std::string QuickInfo(const aiScene* scene);
  const std::vector<gfx::PureRenderData>& render_data() const { return render_parts_; }

  inline bool IsCorrect() const;
protected:
  void InitFromAssimpScene(const aiScene* scene); 

  std::vector<gfx::PureRenderData> render_parts_;
  static util::Logger logger_;
};

}}
// ~~ aff::gfx::Model3d
