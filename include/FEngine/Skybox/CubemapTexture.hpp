#pragma once

#include <string>
#include <GL/glad.h>
#include <vector>

class CubemapTexture {
public:

     void loadFromDirectory(const std::string& path);
     GLuint getID();
     void destroy();

private:

     GLuint m_textureID;

};

