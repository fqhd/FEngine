#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>


class IndexBuffer {
public:

     void init();
     void uploadIndices(unsigned int* indicesData, unsigned int numIndices, GLenum usage);
     void bind();
     void unbind();
     void destroy();

     GLuint getNumIndices();

private:

     GLuint m_numIndices = 0;
     GLuint m_eboID = 0;

};

#endif
