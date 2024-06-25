#include "geometry.h"

Eigen::Vector3f barycentric(Eigen::Vector2i *pts , Eigen::Vector2i P){
    Eigen::Vector3f u = Eigen::Vector3f(pts[2][0]-pts[0][0], pts[1][0]-pts[0][0], pts[0][0]-P[0])
    .cross(Eigen::Vector3f(pts[2][1]-pts[0][1], pts[1][1]-pts[0][1], pts[0][1]-P[1]));
    if (std::abs(u.z())<1) return Eigen::Vector3f(-1,1,1);
    return Eigen::Vector3f(1.f-(u.x()+u.y())/u.z(), u.y()/u.z(), u.x()/u.z()); 
};