#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
public:

     void loadFromFile(const std::string& path);
     GLuint getID();
     void destroy();

private:

     GLuint m_textureID;

};

#endif
