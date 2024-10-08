#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "tgaimage.h"
#include "geometry.h"

void line(Vec2i p0, Vec2i p1, TGAImage& image, const TGAColor& color);
#endif