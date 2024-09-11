cmake_minimum_required(VERSION 3.22)

project(myLittleRedner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


add_executable(littleRender
main.cpp
tgaimage.cpp
model.cpp
geometry.cpp
)

add_executable(sandbox
sandbox.cpp  
tgaimage.cpp
model.cpp
geometry.cpp
rasterizer.cpp
)