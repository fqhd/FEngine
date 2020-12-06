#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

class StaticColor {
public:

     StaticColor(){}
     StaticColor(GLubyte R, GLubyte G, GLubyte B) {
          r = R;
          g = G;
          b = B;
     }

     GLubyte r = 255;
     GLubyte g = 255;
     GLubyte b = 255;

};

class Vertex {
public:

     Vertex(const glm::vec3& p, const glm::vec3& n){
          position = p;
          normal = n;
     }

     glm::vec3 position;
     glm::vec3 normal;

};

#endif
