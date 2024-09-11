#include "rasterizer.h"
#include "tgaimage.h"
#include <random>

#include "model.h"


const TGAColor white = TGAColor(255, 255, 255, 255);

int main() {
  TGAImage image(800, 800, TGAImage::RGB);
  const Model model("../../obj/african_head.obj");
  auto modelFace = model.getFaces();
  auto modelVerts = model.getVerts();
  for (int i=0; i<model.getFaces().size(); ++i) {
    auto face = modelFace[i];
    for (int j=0; j<3; ++j) {
      Vec3f v0 = modelVerts[face[j][0]-1];
      Vec3f v1 = modelVerts[face[(j+1)%3][0]-1];
      line({(int)((v0.x+1.)*image.get_width()/2.), (int)((v0.y+1.)*image.get_height()/2.)},
           {(int)((v1.x+1.)*image.get_width()/2.), (int)((v1.y+1.)*image.get_height()/2.)}, image, white);
    }
  }
  image.flip_vertically();
  image.write_tga_file("output.tga");
  return 0;
}