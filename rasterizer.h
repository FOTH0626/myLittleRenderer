#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <Eigen/Eigen>
#include "TGAImage.h"


void drawLine(TGAImage &image, Eigen::Vector2f point1,Eigen::Vector2f point2,TGAColor);
void swap(Eigen::Vector2f a,Eigen::Vector2f b);
void drawTriangle(Eigen::Vector2f v0,Eigen::Vector2f v1,Eigen::Vector2f v2 ,TGAImage &image,TGAColor color);
void triangle(Eigen::Vector2i* pts, TGAImage &image, TGAColor color);


#endif//RASTERIZER_H