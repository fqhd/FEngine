#ifndef SSAO_BUFFER_H
#define SSAO_BUFFER_H

#include <GL/glew.h>


class SSAOBuffer {
public:

     void init(unsigned int width, unsigned int height);
     void bind();
     void clear();
     void unbind();
     void destroy();

     GLuint getTextureID();

private:

     GLuint m_textureID = 0;
     GLuint m_fboID = 0;

};

#endif
