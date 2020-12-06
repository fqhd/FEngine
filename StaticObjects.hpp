#ifndef STATIC_OBJECTS_H
#define STATIC_OBJECTS_H

#include "BatchRenderer.hpp"
#include "StaticShader.hpp"
#include "Camera3D.hpp"
#include "Settings.hpp"

class StaticObjects {
public:

     void init(Settings& settings);
     void render(Camera3D& camera);
     void destroy();


private:

     //Model functions
     void addSurface(Settings& settings);

     BatchRenderer m_renderer;
     StaticShader m_shader;

};

#endif
