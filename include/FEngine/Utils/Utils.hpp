#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <cstdint>

#include "FEngine/Utils/IndexBuffer.hpp"


namespace Utils{

     std::string readFileToString(const std::string& shaderName);
     bool isInside(const glm::vec2& mousePos, const glm::vec4& destRect);
     bool isInRange(const glm::vec3& a, const glm::vec3& b, float range);
     uint8_t* readFileToBuffer(const std::string& filePath);
     void freeBuffer(uint8_t* buffer);
     void log(const std::string& message);
     IndexBuffer createIndicesBuffer(unsigned int width, unsigned int height);


}
