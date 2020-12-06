#ifndef STATIC_OBJECTS_H
#define STATIC_OBJECTS_H

#include "BatchRenderer.hpp"
#include "StaticShader.hpp"
#include "Camera3D.hpp"

class StaticObjects {
public:

     void init();
     void render(Camera3D& camera);
     void destroy();


private:

     //Model functions
     void addSurface();

     BatchRenderer m_renderer;
     StaticShader m_shader;

};

#endif
