cmake_minimum_required(VERSION 3.22)


add_executable(lesson1
lesson1.cpp)

target_link_libraries(lesson1 PRIVATE littleRenderLibrary)