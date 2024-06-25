#include "rasterizer.h"
#include "TGAImage.h"
#include "geometry.h"
#include <cmath>
#include <Eigen/Eigen>
#include <utility>

TGAColor white = TGAColor(255,255,255,255);

// Bresenham's line drawing algorithm
// Code taken from a stack overflow answer: https://stackoverflow.com/a/16405254
void drawLine(TGAImage &image, Eigen::Vector2f point1,Eigen::Vector2f point2, TGAColor drawColor){
    auto x1 = point1.x();
    auto y1 = point1.y();
    auto x2 = point2.x();
    auto y2 = point2.y();

    int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;

    dx=static_cast<int>(x2-x1);
    dy=static_cast<int>(y2-y1);
    dx1=std::fabs(dx);
    dy1=std::fabs(dy);
    px=2*dy1-dx1;
    py=2*dx1-dy1;

    if(dy1<=dx1)
    {
        if(dx>=0)
        {
            x=x1;
            y=y1;
            xe=x2;
        }
        else
        {
            x=x2;
            y=y2;
            xe=x1;
        }   
        Eigen::Vector2i point = Eigen::Vector2i(x, y);
        image.set(point.x(),point.y(),drawColor);
        for(i=0;x<xe;i++)
        {
            x=x+1;
            if(px<0)
            {
                px=px+2*dy1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    y=y+1;
                }
                else
                {
                    y=y-1;
                }
                px=px+2*(dy1-dx1);
            }
        Eigen::Vector2f point = Eigen::Vector2f(x, y);
        image.set(point.x(),point.y(),drawColor);
        }
    }
    else
    {
        if(dy>=0)
        {
            x=x1;
            y=y1;
            ye=y2;
        }
        else
        {
            x=x2;
            y=y2;
            ye=y1;
        }
        Eigen::Vector2f point = Eigen::Vector2f(x, y);
            image.set(point.x(),point.y(),drawColor);
        for(i=0;y<ye;i++)
        {
            y=y+1;
            if(py<=0)
            {
                py=py+2*dx1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    x=x+1;
                }
                else
                {
                    x=x-1;
                }
                py=py+2*(dx1-dy1);
            }
//            delay(0);
            Eigen::Vector2f point = Eigen::Vector2f(x, y);
            image.set(point.x(),point.y(),drawColor);
        }
    }
}

void drawTriangle(Eigen::Vector2f v0,Eigen::Vector2f v1,Eigen::Vector2f v2 ,TGAImage &image,TGAColor color){
    
    //dont need to draw a degenerated triangle
    if (v0.x() == v1.x() && v1.x() == v2.x()) return;
    if (v0.y() == v1.y() && v1.y() == v2.y()) return;

    if (v0.y() > v1.y()) std::swap(v0,v1);
    if (v0.y() > v2.y()) std::swap(v0,v2);
    if (v1.y() > v2.y()) std::swap(v1,v2);
    //now v0 is lowest ,v2 higest ,v1 is the middle
    int totalHeight = v2.y()-v0.y();
    for (int i =0; i < totalHeight; ++i){
        bool halfHeight = i > (v1.y()-v0.y()) || v1.y() == v0.y();
        int segment_height = halfHeight? v2.y()-v1.y() : v1.y()-v0.y();
        float leftPoint = (float)i/totalHeight;
        float rightPoint = (float)(i-(halfHeight?v1.y()-v0.y() : 0))/segment_height;
        Eigen::Vector2f leftLerpPoint = v0 + (v2-v0)*leftPoint;
        Eigen::Vector2f rightLerpPoint = halfHeight ? v1+(v2-v1)*rightPoint : v0 + (v1-v0)*rightPoint;
        if (leftLerpPoint.x()<rightLerpPoint.x()) {std::swap(leftLerpPoint,rightLerpPoint);}
        for(int j =static_cast<int>(leftLerpPoint.x()); j < static_cast<int>(rightLerpPoint.x()); ++j) {
            image.set(j, static_cast<int>(v0.y()+i),color);
            };
    };

}

void triangle(Eigen::Vector2i* pts, TGAImage &image, TGAColor color) { 
    Eigen::Vector2i bboxmin(image.get_width()-1,  image.get_height()-1); 
    Eigen::Vector2i bboxmax(0, 0); 
    Eigen::Vector2i clamp(image.get_width()-1, image.get_height()-1); 
    for (int i=0; i<3; i++) { 
        bboxmin.x()= std::max(0, std::min(bboxmin.x(), pts[i].x()));
	bboxmin.y() = std::max(0, std::min(bboxmin.y(), pts[i].y()));

	bboxmax.x() = std::min(clamp.x(), std::max(bboxmax.x(), pts[i].x()));
	bboxmax.y() = std::min(clamp.y(), std::max(bboxmax.y(), pts[i].y()));
    } 
    Eigen::Vector2i P; 
    for (P.x()=bboxmin.x(); P.x()<=bboxmax.x(); P.x()++) { 
        for (P.y()=bboxmin.y(); P.y()<=bboxmax.y(); P.y()++) { 
            Eigen::Vector3f bc_screen  = barycentric(pts, P); 
            if (bc_screen.x()<0 || bc_screen.y()<0 || bc_screen.z()<0) continue; 
            image.set(P.x(), P.y(), color); 
        } 
    } 
} 
