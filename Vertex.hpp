#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

class Vertex {
public:

     Vertex(const glm::vec3& p, const glm::vec2& u, const glm::vec3 n){
          position = p;
          uv = u;
          normal = n;
     }
     
     glm::vec3 position;
     glm::vec2 uv;
     glm::vec3 normal;

};

#endif
