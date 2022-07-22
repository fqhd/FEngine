#pragma once

#include "glad.h"
#include <glm/glm.hpp>
#include <vector>
#include "Color.hpp"

struct Object {
    Object(const glm::mat4& m, const Color& c){
        matrix = m;
        color = c;
    }
    glm::mat4 matrix;
    Color color;
};

class InstanceRenderer {
public:

    void init();
    void begin();
    void add(const glm::mat4& matrix, const Color& color);
    void end();
    void draw();
    void destroy();

private:

    GLuint vaoID;
    GLuint vboID;
    GLuint instanceBuffer;
    std::vector<Object> objects;

};