#include "model.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


Model::Model(const std::string &filename) {
  std::ifstream file(filename);
  if ( !file.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }
  std::string line;
  while (std::getline(file, line)){
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if(type == "v") {
      Vec3f v;
      iss >> v.x >> v.y >> v.z;
      verts_.push_back(v);
    }else if(type == "vt"){
        Vec2f vt;
        iss >> vt.x >> vt.y;
        uv_.push_back(vt);
    }
    else if (type == "vn"){
        Vec3f vn;
        iss >> vn.x >> vn.y >> vn.z;
        norms_.push_back(vn);
    }
    else if (type == "f"){
      std::array<std::array<unsigned short, 3>, 3> face{};
      char slash;
      for (int i = 0; i < 3; i++) {
        iss >> face[i][0] >> slash >> face[i][1] >> slash >> face[i][2];
      }
      faces_.push_back(face);
    }

  }
  file.close();
  std::cout << "Loaded" << verts_.size() << " vertices" << std::endl;
  std::cout << "Loaded" << uv_.size() << " uv" << std::endl;
  std::cout << "Loaded" << norms_.size() << " normals" << std::endl;
  std::cout << "Loaded" << faces_.size() << " faces" << std::endl;

}

std::vector<std::array<unsigned short, 3>> Model::getFaceTrianglesIndexList() const {
  std::vector<std::array<unsigned short,3>> FaceTrianglesIndexList;
  for( const auto& triangleIndexInfo : faces_) {
    FaceTrianglesIndexList.push_back(
      {triangleIndexInfo.at(0).at(0),
      triangleIndexInfo.at(1).at(0),
      triangleIndexInfo.at(2).at(0)});
  }
  return std::move(FaceTrianglesIndexList);
}

std::vector<std::array<unsigned short, 3>> Model::getFaceUVsIndexList() const {
  std::vector<std::array<unsigned short,3>> FaceUVsIndexList;
  for( const auto& triangleIndexInfo : faces_) {
    FaceUVsIndexList.push_back(
      {triangleIndexInfo.at(0).at(1),
      triangleIndexInfo.at(1).at(1),
      triangleIndexInfo.at(2).at(1)});
  }
  return std::move(FaceUVsIndexList);
}

std::vector<std::array<unsigned short, 3>> Model::getFaceNormalsIndexList() const {
  std::vector<std::array<unsigned short,3>> FaceNormalsIndexList;
  for( const auto& triangleIndexInfo : faces_) {
    FaceNormalsIndexList.push_back(
      {triangleIndexInfo.at(0).at(2),
      triangleIndexInfo.at(1).at(2),
      triangleIndexInfo.at(2).at(2)});
  }
  return std::move(FaceNormalsIndexList);
}




