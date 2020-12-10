#ifndef SSAO_BLUE_BUFFER_H
#define SSAO_BLUE_BUFFER_H

#include <GL/glew.h>


class SSAOBlurBuffer {
public:

     void init(unsigned int width, unsigned int height);
     void bind();
     void clear();
     void unbind();
     void destroy();

     GLuint getID();


private:

     GLuint m_textureID = 0;
     GLuint m_fboID;


};

#endif
