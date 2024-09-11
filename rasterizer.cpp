#include "rasterizer.h"
#include "geometry.h"
//breseham line drawing algorithm from games101 homework 
void line(const Vec2i p1, const Vec2i p2, TGAImage &image, const TGAColor& color) {
  int x1 = p1.x;
  int y1 = p1.y;
  int x2 = p2.x;
  int y2 = p2.y;

  int x, y, xe, ye ;
  int dx = x2 - x1;
  int dy = y2 - y1;
  int dx1 = std::abs(dx);
  int dy1 = std::abs(dy);
  int px = 2 * dy1 - dx1;
  int py = 2 * dx1 - dy1;
    if (dy1 <= dx1) {
      if (dx >= 0) {
        x = x1;
        y = y1;
        xe =x2;
      }else {
        x =x2;
        y = y2;
        xe = x1;
      }
      image.set(x, y, color);
      for (int i = 0; x < xe; i++) {
        x = x + 1;
        if (px < 0) {
          px = px + 2 * dy1;
        }else {
          if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
            y = y + 1;
          }else {
            y = y - 1;
          }
          px = px + 2 * (dy1 - dx1);
        }
        image.set(x, y, color);
      }
    }else {
      if (dy >= 0) {
        x = x1;
        y = y1;
        ye = y2;
      }else {
        x = x2;
        y = y2;
        ye = y1;
      }
      image.set(x, y, color);
      for (int i = 0; y < ye; i++) {
        y = y + 1;
        if (py <= 0) {
          py = py + 2 * dx1;
        }else {
          if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
            x = x + 1;
          }else {
            x = x - 1;
          }
          py = py + 2 * (dx1 - dy1);
        }
        image.set(x, y, color);
      }
    }
}
