#ifndef DYNAMIC_TERRAIN_H
#define DYNAMIC_TERRAIN_H

#include <glm/gtc/noise.hpp>

#include "Camera.hpp"
#include "Terrain.hpp"
#include "DynamicTerrainShader.hpp"
#include "IndexBuffer.hpp"
#include "Utils.hpp"


class DynamicTerrain {
public:

     void init(unsigned int resolution);
     void update(Camera& camera);
     void render(Camera& camera);
     void destroy();


private:

     void updateTerrainBasedOnPosition(const glm::vec2& position);

     //Objects
     Terrain m_terrain;
     DynamicTerrainShader m_shader;
     IndexBuffer m_indexBuffer;
     Vertex* m_vertices = nullptr;
     unsigned int m_resolution;

     //Primitive Variables
     glm::vec2 m_position;

};

#endif
