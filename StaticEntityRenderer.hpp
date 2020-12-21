#ifndef STATIC_ENTITY_RENDERER_H
#define STATIC_ENTITY_RENDERER_H

#include <algorithm>
#include <vector>

#include "GBufferShader.hpp"
#include "Entity.hpp"
#include "BatchedMesh.hpp"
#include "Camera.hpp"


class StaticEntityRenderer {
public:

     void init();
     void batchEntities(std::vector<Entity>& entities);
     void render(Camera& camera);
     void destroy();

private:

     static bool compare(Entity a, Entity b);

     GBufferShader m_shader;

     GLuint m_iboID = 0;
     std::vector<glm::mat4> m_matrices; // Matrices for each mesh that will be rendered
     std::vector<BatchedMesh> m_meshes; // Batched mesh containing the model information as well as the offsent for the matrices vector and number of instances of that entity drawn to the screen


};

#endif
