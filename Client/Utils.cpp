#include "Utils.hpp"

std::string Utils::loadShader(const char* shaderName){
	std::string shaderCode = "";
	std::string line;
	std::ifstream is;
	is.open(shaderName);

	while(std::getline(is, line)){
		shaderCode += line + "\n";
	}

	is.close();
	return shaderCode;
}

bool Utils::isInside(const glm::vec2& pos, const glm::vec4& destRect){
    return (pos.x >= destRect.x && pos.x <= destRect.x + destRect.z && pos.y >= destRect.y && pos.y <= destRect.y + destRect.w);
}

bool Utils::isInRange(const glm::vec3& a, const glm::vec3& b, float range){
	return std::fabs(glm::length(b - a)) < range;
}
