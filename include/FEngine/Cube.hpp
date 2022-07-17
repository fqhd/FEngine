#pragma once

#include <glad.h>

class Cube
{
public:
    void init();
    void render() const;
    void destroy();

private:
    GLuint m_vaoID = 0;
    GLuint m_vboID = 0;
};