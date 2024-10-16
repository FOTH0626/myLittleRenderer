#include "model.h"
#include "rasterizer.h"
#include "tgaimage.h"
#include "common.h"
//
// Created by foth on 24-9-28.
//


int main() {

  const Model model("../../obj/african_head.obj");
  const auto modelFace = model.getFaces();
  const auto modelVerts = model.getVerts();

  TGAImage gamma_head(800, 800, TGAImage::RGB);
  Vec3f light_dir{0,0,-1.};
  for (int i=0; i<model.getFaces().size(); ++i) {
    auto face = modelFace[i];
    const std::array face_triangle = {Vec3i{(int)((modelVerts[face[0][0]-1].x+1.)*gamma_head.get_width()/2.),
                                            (int)((modelVerts[face[0][0]-1].y+1.)*gamma_head.get_height()/2.),
                                            (int)((modelVerts[face[0][0]-1].z+1.)*gamma_head.get_height()/2.)},
                                         Vec3i{(int)((modelVerts[face[1][0]-1].x+1.)*gamma_head.get_width()/2.),
                                               (int)((modelVerts[face[1][0]-1].y+1.)*gamma_head.get_height()/2.),
                                               (int)((modelVerts[face[1][0]-1].z+1.)*gamma_head.get_height()/2.)},
                                         Vec3{(int)((modelVerts[face[2][0]-1].x+1.)*gamma_head.get_width()/2.),
                                               (int)((modelVerts[face[2][0]-1].y+1.)*gamma_head.get_height()/2.),
                                               (int)((modelVerts[face[2][0]-1].z+1.)*gamma_head.get_height()/2.)}};
    Vec3f world_coords[3];
    for (int j=0; j<3; ++j) {
      world_coords[j] = modelVerts[face[j][0]-1];
    }
    Vec3f n = cross((world_coords[2]-world_coords[0]),(world_coords[1]-world_coords[0]));
    n.normalize();
    float intensity = dot(n,light_dir);
    if (intensity>0) {
      triangle_bbox(face_triangle, gamma_head, TGAColor(intensity*255, intensity*255, intensity*255, 255));
    }
  }

  gamma_head.flip_vertically();
  gamma_head.write_tga_file("lesson2_gamma_head.tga");

  return 0;
}