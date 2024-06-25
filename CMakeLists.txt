cmake_minimum_required(VERSION 3.15)

project (myLittleRenderer)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

add_executable(myLittleRenderer 
main.cpp
TGAImage.cpp TGAImage.h 
rasterizer.cpp rasterizer.h
geometry.cpp geometry.h
model.cpp model.h
)
target_link_libraries( ${PROJECT_NAME} Eigen3::Eigen)

