#ifndef CUBE_MAP_TEXTURE_H
#define CUBE_MAP_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <vector>

class CubemapTexture {
public:

     void loadFromDirectory(const std::string& path);
     GLuint getID();
     void destroy();

private:

     GLuint m_textureID;

};

#endif
