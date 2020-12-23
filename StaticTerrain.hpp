#ifndef STATIC_TERRAIN_H
#define STATIC_TERRAIN_H

#include <vector>
#include <GL/glew.h>

#include "Texture.hpp"
#include "Terrain.hpp"
#include "StaticTerrainShader.hpp"
#include "Camera.hpp"


class StaticTerrain {
public:

     void loadFromFile(Texture* texture, const std::string& filepath, unsigned int precisionFactor, float size, float heightScale, float textureScale);
     void render(Camera& camera);
     void destroy();

private:

     Texture* m_texture = nullptr;
     Terrain m_terrain;
     StaticTerrainShader m_shader;



};

#endif
