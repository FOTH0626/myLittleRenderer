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

void line_vertical(Vec2i p0, Vec2i p1, TGAImage &image, const TGAColor &color) {
  if (p0.y != p1.y) {
    std::cerr << "Not a vertical line" << std::endl;
    return;
  }
  const int const_y = p0.y;
  if (p0.x > p1.x) std::swap(p0, p1);
  for (int x = p0.x; x <= p1.x; x++) {
    image.set(x, const_y, color);
  }
}

void triangle(const std::array<Vec3i, 3> &verts, const TGAImage &image, const TGAColor &color) {
  auto point0 = verts.at(0);
  auto point1 = verts.at(1);
  auto point2 = verts.at(2);
  //avoid a triangle degenerating into a line
  if (std::abs(point0.y-point1.y)<=.1 && std::abs(point0.y - point2.y)<= .1) return;
  //sort three point3 , now they sort by y in ascending order, we call them A , B , C

  if (point0.y > point1.y) std::swap(point0, point1);
  if (point1.y > point2.y) std::swap(point1, point2);
  if (point0.y > point1.y) std::swap(point0, point1);
  //calc the slope and draw triangle


  for (int y = point0.y; y <= point2.y; ++y) {
    auto pointA = point0 + (point2 - point0) * static_cast<float>(y - point0.y) / (point2.y - point0.y);
    auto pointB = y >= point1.y ? point1 + (point2 - point1) * static_cast<float>(y - point1.y) / (point2.y - point1.y)
                                      : point0 + (point1 - point0) * static_cast<float>(y - point0.y) / (point1.y - point0.y);
    if (pointA.x > pointB.x) std::swap(pointA, pointB);
    for (int x = pointA.x; x <= pointB.x; ++x) {
      image.set(x, y, color);
    }
  }
}

BoundingBox boundingBox(const std::array<Vec2i,3>& triangle,const TGAImage& image) {
  Vec2i boundingBoxMin{image.get_width() - 1, image.get_height() - 1};
  Vec2i boundingBoxMax{0, 0};
  Vec2i clamp(image.get_width() - 1, image.get_height() - 1);
  for (int i = 0; i < 3; i++) {
    boundingBoxMin.x = std::max(0, std::min(boundingBoxMin.x, triangle[i].x));
    boundingBoxMin.y = std::max(0, std::min(boundingBoxMin.y, triangle[i].y));

    boundingBoxMax.x = std::min(clamp.x, std::max(boundingBoxMax.x, triangle[i].x));
    boundingBoxMax.y = std::min(clamp.y, std::max(boundingBoxMax.y, triangle[i].y));
  }
  return {boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.x, boundingBoxMax.y};
};

Vec3f barycentric(const std::array<Vec2f, 3> &pts, const Vec2i &P) {
  Vec3f u = cross(Vec3f{pts[2].x - pts[0].x, pts[1].x - pts[0].x, pts[0].x - P.x},
                  Vec3f{pts[2].y - pts[0].y, pts[1].y - pts[0].y, pts[0].y - P.y});
  if (std::abs(u.z) < 1) return Vec3f{-1, 1, 1};
  return Vec3f{1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z};
}

void triangle_bbox(const std::array<Vec3i,3>& triangle,const TGAImage &image, const TGAColor &color) {
  BoundingBox bbox = boundingBox({{Vec2i{triangle[0].x, triangle[0].y},
                                   Vec2i{triangle[1].x, triangle[1].y},
                                   Vec2i{triangle[2].x, triangle[2].y}}}, image);
  for (int x = bbox.minX; x <= bbox.maxX; x++) {
    for (int y = bbox.minY; y <= bbox.maxY; y++) {
      Vec2i P{x, y};
      Vec3f bc_screen = barycentric({{Vec2f{triangle[0].x, triangle[0].y},
                                      Vec2f{triangle[1].x, triangle[1].y},
                                      Vec2f{triangle[2].x, triangle[2].y}}}, P);
      if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
      image.set(x, y, color);
    }
  }
}






