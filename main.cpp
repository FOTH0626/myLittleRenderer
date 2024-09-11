#include "tgaimage.h"
#include <vector>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
	image.flip_vertically(); // I want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
  std::vector<int> vec;
	return 0;
}

