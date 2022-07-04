#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>


class Vertex {
public:

     Vertex(){}
     Vertex(const glm::vec3& p, const glm::vec3& n, const glm::vec2& u){
          position = p;
          normal = n;
          uv = u;
     }

     glm::vec3 position;
     glm::vec3 normal;
     glm::vec2 uv;

};

#endif
