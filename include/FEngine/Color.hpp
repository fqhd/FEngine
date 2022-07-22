#pragma once

#include <glad.h>

struct Color
{
    Color(){
        r = 0;
        g = 0;
        b = 0;
    }
    Color(GLubyte R, GLubyte G, GLubyte B)
    {
        r = R;
        g = G;
        b = B;
    }
    GLubyte r;
    GLubyte g;
    GLubyte b;
};