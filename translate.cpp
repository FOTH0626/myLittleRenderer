#include <cmath>
#include <Eigen/Eigen>
#include "translate.h"

Eigen::Matrix3f setMoveMatrix(float xMove, float yMove){
    Eigen::Matrix3f move = Eigen::Matrix3f::Identity();
    move << 1, 0, xMove,
            0, 1, yMove,
            0, 0, 1;
    return move;
};
Eigen::Matrix3f setScaleMatrix(float scale){
    Eigen::Matrix3f scaleMatrix = Eigen::Matrix3f::Identity();
    scaleMatrix << scale, 0, 0,
                   0, scale, 0,
                   0, 0, 1;
    return scaleMatrix;
};
Eigen::Matrix3f setRotationMatrix(float angle){
    Eigen::Matrix3f rotationMatrix = Eigen::Matrix3f::Identity();
    rotationMatrix << std::cos(angle), -std::sin(angle), 0,
                      std::sin(angle), std::cos(angle), 0,
                      0, 0, 1;
    return rotationMatrix;
};
Eigen::Matrix4f setRotationMatrixZaxis(float angle){
    Eigen::Matrix4f rotationMatrix = Eigen::Matrix4f::Identity();
    rotationMatrix << std::cos(angle), -std::sin(angle), 0, 0,
                      std::sin(angle), std::cos(angle), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1;
    return rotationMatrix;
};
Eigen::Matrix4f setRotationMatrixYaxis(float angle){
    Eigen::Matrix4f rotationMatrix = Eigen::Matrix4f::Identity();
    rotationMatrix << std::cos(angle), 0, std::sin(angle), 0,
                      0, 1, 0, 0,
                      -std::sin(angle), 0, std::cos(angle), 0,
                      0, 0, 0, 1;
    return rotationMatrix;
};
Eigen::Matrix4f setRotationMatrixXaxis(float angle){
    Eigen::Matrix4f rotationMatrix = Eigen::Matrix4f::Identity();
    rotationMatrix << 1, 0, 0, 0,
                      0, std::cos(angle), -std::sin(angle), 0,
                      0, std::sin(angle), std::cos(angle), 0,
                      0, 0, 0, 1;
    return rotationMatrix;
};


Eigen::Matrix3f setViewMatrix(){
    
};


// Eigen::Matrix3f getProjectionMatrix();
// Eigen::Matrix3f setProjectionMatrix();
