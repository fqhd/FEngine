#ifndef SURFACE_H
#define SURFACE_H

#include <GL/glew.h>
#include "Vertex.hpp"
#include "Settings.hpp"

class Surface {
public:

     void init(Settings& settings);
     void render();
     void destroy();

private:

     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;
     GLuint m_numVertices = 0;


};
#endif
