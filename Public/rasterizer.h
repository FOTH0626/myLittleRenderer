#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "tgaimage.h"
#include "geometry.h"

void line(Vec2i p0, Vec2i p1, TGAImage& image, const TGAColor& color);

void line_vertical(Vec2i p0, Vec2i p1, TGAImage& image, const TGAColor& color);

void triangle(const std::array<Vec2i,3> &, const TGAImage& image, const TGAColor& color);

Vec3f barycentric(const std::array<Vec2f, 3>& tri, const Vec2i& P);

void triangle_bbox(const std::array<Vec3i, 3>&, const TGAImage &image, const TGAColor &color);

struct BoundingBox {
  int minX;
  int minY;
  int maxX;
  int maxY;
};
BoundingBox boundingBox(const std::array<Vec2i,3>& triangle, const TGAImage& image);

Vec2i floatPointToInt(const Vec2f& point, const TGAImage& image);

#endif