#ifndef CUBE_TEXTURE_H
#define CUBE_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <vector>

class CubeTexture {
public:

     void loadFromFile(const std::vector<std::string>& faces);
     GLuint getID();
     void destroy();

private:

     GLuint m_textureID;

};

#endif
