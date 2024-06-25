#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

#include <Eigen/Eigen>

Eigen::Matrix3f setMoveMatrix(float xMove, float yMove);
Eigen::Matrix3f setScaleMatrix(float scale);
Eigen::Matrix3f setRotationMatrix(float angle);
Eigen::Matrix4f setRotationMatrixZaxis(float angle);
Eigen::Matrix4f setRotationMatrixYaxis(float angle);
Eigen::Matrix4f setRotationMatrixXaxis(float angle);

Eigen::Matrix3f setViewMatrix();

Eigen::Matrix3f setProjectionMatrix();

#endif // MVP_HP