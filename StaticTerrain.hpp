#ifndef STATIC_TERRAIN_H
#define STATIC_TERRAIN_H

#include <vector>
#include <GL/glew.h>

#include "Terrain.hpp"
#include "StaticTerrainShader.hpp"
#include "Camera.hpp"


class StaticTerrain {
public:

     void loadFromFile(const std::string& filepath, unsigned int precisionFactor, float size, float heightScale);
     void render(Camera& camera);
     void destroy();

private:

     Terrain m_terrain;
     StaticTerrainShader m_shader;



};

#endif
