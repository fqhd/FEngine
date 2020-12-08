#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "Cube.hpp"
#include "CubemapShader.hpp"
#include "Camera3D.hpp"
#include "Assets.hpp"

class Cubemap {
public:

     void init();
     void update();
     void render(Camera3D& camera, Assets& assets);
     void destroy();

private:


     Cube m_cube;
     CubemapShader m_shader;



};

#endif
