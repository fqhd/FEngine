#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include <string>

#include "Utils.hpp"


class GBuffer {
public:

     void init(unsigned int width, unsigned int height);
     void bind();
     void unbind();
     void destroy();
     void clear();

     GLuint getPositionTextureID();
     GLuint getAlbedoTextureID();
     GLuint getNormalTextureID();


private:


     GLuint m_fboID = 0;
     GLuint m_rboID = 0;
     GLuint m_positionTextureID = 0;
     GLuint m_albedoTextureID = 0;
     GLuint m_normalTextureID = 0;



};

#endif
