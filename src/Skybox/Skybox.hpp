#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>

#include "Cube.hpp"
#include "SkyboxShader.hpp"
#include "CubemapTexture.hpp"
#include "Camera.hpp"


class Skybox{
public:

     void init(const std::string& dayTexturePath, const std::string& nightTexturePath);
     void render(Camera& camera);
     void destroy();

private:

     CubemapTexture m_dayTexture;
     CubemapTexture m_nightTexture;
     Cube m_cube;
     SkyboxShader m_shader;

};

#endif
