#include "geometry.h"
#include "model.h"
#include "rasterizer.h"
#include "common.h"

#include <iostream>
//
// Created by foth on 24-10-2.
//
void triangle_zbuffer(const std::array<Vec3i,3>& triangle, std::vector<float>& zBuffer, const TGAImage& image, const TGAColor &color) {
  BoundingBox bbox = boundingBox({{Vec2i{triangle[0].x, triangle[0].y},
                                   Vec2i{triangle[1].x, triangle[1].y},
                                   Vec2i{triangle[2].x, triangle[2].y}}}, image);
  for (int x = bbox.minX; x <= bbox.maxX; x++) {
    for (int y = bbox.minY; y <= bbox.maxY; y++) {
      Vec2i P{x, y};
      Vec3f bc_screen = barycentric({Vec2f{triangle[0].x, triangle[0].y},
                                      Vec2f{triangle[1].x, triangle[1].y},
                                      Vec2f{triangle[2].x, triangle[2].y}}, P);
      if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
      float z = (triangle[0].z * bc_screen.x + triangle[1].z * bc_screen.y + triangle[2].z * bc_screen.z + 1.0f) / 2.0f;
      int index = x + y * image.get_width();
      if (zBuffer[index] < z) {
        zBuffer[index] = z;
        image.set(x, y, color);
      }
    }
  }
}


int main() {
  TGAImage image(800, 800, TGAImage::RGB);
  const Model model("../../obj/african_head.obj");
  std::vector<float> zBuffer(image.get_height() * image.get_width(), -std::numeric_limits<float>::max());
  auto modelFaces = model.getFaces();
  auto modelVerts = model.getVerts();
  for (int i = 0;i < modelFaces.size(); ++i) {
    auto face = modelFaces[i];
    const std::array face_triangle = {Vec3i{(int)((modelVerts[face[0][0]-1].x+1.)*image.get_width()/2.),
                                          (int)((modelVerts[face[0][0]-1].y+1.)*image.get_height()/2.),
                                          (int)((modelVerts[face[0][0]-1].z+1.)*image.get_height()/2.)},
                                      Vec3i{(int)((modelVerts[face[1][0]-1].x+1.)*image.get_width()/2.),
                                            (int)((modelVerts[face[1][0]-1].y+1.)*image.get_height()/2.),
                                            (int)((modelVerts[face[1][0]-1].z+1.)*image.get_height()/2.)},
                                      Vec3i{(int)((modelVerts[face[2][0]-1].x+1.)*image.get_width()/2.),
                                            (int)((modelVerts[face[2][0]-1].y+1.)*image.get_height()/2.),
                                            (int)((modelVerts[face[2][0]-1].z+1.)*image.get_height()/2.)}};
    Vec3f light_dir{0,0,-1.};
    Vec3f world_coords[3];
    for (int j=0; j<3; ++j) {
      world_coords[j] = modelVerts[face[j][0]-1];
    }
    Vec3f n = cross((world_coords[2]-world_coords[0]),(world_coords[1]-world_coords[0]));
    n.normalize();
    float intensity = dot(n, light_dir) ;
    if (intensity>0) {
      triangle_zbuffer(face_triangle, zBuffer, image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
    }
  }
  image.flip_vertically();
  image.write_tga_file("lesson3_zbuffer.tga");
  return 0;
}