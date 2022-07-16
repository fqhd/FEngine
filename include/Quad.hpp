#pragma once

#include <glad.h>

class Quad {
public:
    void init();
    void draw();
    void destroy();
    GLuint vaoID = 0;
    GLuint vboID = 0;
};