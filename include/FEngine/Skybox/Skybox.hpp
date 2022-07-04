#pragma once

#include <string>

#include "../Renderer/Cube.hpp"
#include "../Shaders/SkyboxShader.hpp"
#include "CubemapTexture.hpp"
#include "../Camera/Camera.hpp"


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
