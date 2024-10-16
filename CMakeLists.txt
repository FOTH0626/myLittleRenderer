cmake_minimum_required(VERSION 3.22)

project(myLittleRedner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(Public)

add_subdirectory(Sample)

add_library(littleRenderLibrary
        Private/tgaimage.cpp
        Private/model.cpp
        Private/geometry.cpp
        Private/rasterizer.cpp
)

