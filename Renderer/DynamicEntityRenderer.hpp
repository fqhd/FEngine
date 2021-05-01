#ifndef DYNAMIC_ENTITY_RENDERER_H
#define DYNAMIC_ENTITY_RENDERER_H

#include <vector>
#include <algorithm>

#include "Camera.hpp"
#include "Entity.hpp"
#include "GBufferShader.hpp"
#include "BatchedMesh.hpp"
#include "GBufferShader.hpp"


class DynamicEntityRenderer {
public:

     void init();
     void render(std::vector<Entity>& entities, Camera& camera);
     void destroy();

private:

     static bool compare(Entity a, Entity b);

     GBufferShader m_shader;
     GLuint m_iboID = 0;

};

#endif
