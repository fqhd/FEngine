#pragma once

#include <vector>
#include <GL/glad.h>

#include "../Renderer/Texture.hpp"
#include "Terrain.hpp"
#include "../Shaders/TerrainShader.hpp"
#include "../Camera/Camera.hpp"
#include "../Utils/Transform.hpp"
#include "../Utils/IndexBuffer.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Image.hpp"


class StaticTerrain {
public:

     void init(Texture* texture, const std::string& filepath, unsigned int precisionFactor, float size, float heightScale, float textureScale);
     void init(Texture* texture, const std::string& filepath, float size, float heightScale, float textureScale);
     void render(Camera& camera);
     void destroy();

     Transform transform;

private:

     Texture* m_texture = nullptr;
     Terrain m_terrain;
     TerrainShader m_shader;
     IndexBuffer m_indexBuffer;



};
