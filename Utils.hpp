#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <cstdint>

namespace Utils{

     std::string loadShader(const std::string& shaderName);
     bool isInside(const glm::vec2& mousePos, const glm::vec4& destRect);
     bool isInRange(const glm::vec3& a, const glm::vec3& b, float range);
     uint8_t* readFileToBuffer(const std::string& filePath);
     void freeBuffer(uint8_t* buffer);
     void log(const std::string& message);


}

#endif
