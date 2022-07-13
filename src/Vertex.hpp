#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex {
public:
    Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 t){
        position = p;
        normal = n;
        uv = t;
    }
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    GLubyte id;
};