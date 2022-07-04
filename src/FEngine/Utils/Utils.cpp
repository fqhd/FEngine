#include "Utils.hpp"


std::string Utils::readFileToString(const std::string& shaderName) {
	std::string shaderCode = "";
	std::string line;
	std::ifstream is;
	is.open(shaderName);
	if(is.fail()){
		log("Failed to find file: " + shaderName);
		is.close();
		return shaderCode;
	}

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

void Utils::log(const std::string& message){
	printf("%s\n", message.c_str());
}

IndexBuffer Utils::createIndicesBuffer(unsigned int width, unsigned int height){
	IndexBuffer buffer;

	std::vector<unsigned int> indices;
     for(unsigned int z = 0; z < height - 1; z++){
          for(unsigned int x = 0; x < width - 1; x++){

               indices.emplace_back(z * height + x);
               indices.emplace_back(z * height + x + width);
               indices.emplace_back(z * height + x + 1);
               indices.emplace_back(z * height + x + 1);
               indices.emplace_back(z * height + x + width);
               indices.emplace_back(z * height + x + width + 1);

          }
     }

     buffer.init();
     buffer.uploadIndices(indices.data(), indices.size(), GL_STATIC_DRAW);
	return buffer;
}
