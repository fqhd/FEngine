#ifndef DYNAMIC_TERRAIN_H
#define DYNAMIC_TERRAIN_H

#include <glm/gtc/noise.hpp>

#include "Camera.hpp"
#include "Terrain.hpp"
#include "TerrainShader.hpp"
#include "IndexBuffer.hpp"
#include "Utils.hpp"


class DynamicTerrain {
public:

     void init(unsigned int resolution);
     void render(Camera& camera);
     void destroy();


private:

     void createAndUploadTerrainVertices();

     //Objects
     Terrain m_terrain;
     TerrainShader m_shader;
     IndexBuffer m_indexBuffer;
     unsigned int m_resolution;

     //Primitive Variables
     glm::vec2 m_position;

};

#endif
