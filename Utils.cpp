#include "Utils.hpp"


std::string Utils::loadShader(const std::string& shaderName) {
	std::string shaderCode = "";
	std::string line;
	std::ifstream is;
	is.open(shaderName);

	while(std::getline(is, line)) {
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

uint8_t* Utils::readFileToBuffer(const std::string& filePath) {

    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
	   perror(filePath.c_str());
	   return nullptr;
    }

    file.seekg(0, std::ios::end);

    unsigned int fileSize = (unsigned int)file.tellg();
    file.seekg(0, std::ios::beg);

    fileSize -= (unsigned int)file.tellg();

	//Creating new buffer
    uint8_t* buffer = new uint8_t[fileSize];

	//Reading data into buffer
    file.read((char*)buffer, fileSize);
    file.close();

    return buffer;
}

void Utils::freeBuffer(uint8_t* buffer){
	delete[] buffer;
}

void Utils::log(LOG_TYPE type, const std::string& message){
	if(type == CONSOLE){
		printf("%s\n", message.c_str());
	}else{
		std::ofstream os;
		os.open("logs.txt");
		os << message << std::endl;
		os.close();
	}
}
