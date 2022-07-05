#pragma once

#include <GL/glew.h>

struct Color {
    Color(GLubyte R, GLubyte G, GLubyte B){
        r = R;
        g = G;
        b = B;
    }
    GLubyte r;
    GLubyte g;
    GLubyte b;
};