#pragma once
#include <GL/glad.h>


class SSAOBlurBuffer {
public:

     void init(unsigned int width, unsigned int height);
     void bind();
     void clear();
     void unbind();
     void destroy();

     GLuint getTextureID();


private:

     GLuint m_textureID = 0;
     GLuint m_fboID;


};
