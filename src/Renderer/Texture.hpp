#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>


class Texture {
public:

     void init(const std::string& path);
     void bind();
     void unbind();
     void destroy();

     GLuint getID();

private:

     GLuint m_textureID = 0;

};

#endif
