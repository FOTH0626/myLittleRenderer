#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "geometry.h"

class Model{
  public:
    Model() = delete;
    explicit Model(const std::string& filename);
    [[nodiscard]] std::vector<Vec3f> getVerts() const {return verts_;}
    [[nodiscard]] std::vector<Vec2f> getUV() const {return uv_;}
    [[nodiscard]] std::vector<Vec3f> getNorms() const {return norms_;}
    [[nodiscard]] std::vector<std::array<std::array<unsigned short,3>, 3>> getFaces() const {return faces_;}
  private:
    std::vector<Vec3f> verts_;
    std::vector<Vec2f> uv_;
    std::vector<Vec3f> norms_;
    std::vector<std::array<std::array<unsigned short,3>, 3>> faces_;

};

#endif