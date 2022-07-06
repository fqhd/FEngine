#pragma once

#include <GL/glew.h>

class Quad {
public:
    void init();
    void draw();
    GLuint vaoID = 0;
    GLuint vboID = 0;
};