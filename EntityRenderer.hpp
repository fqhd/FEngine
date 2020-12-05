#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include "ModelShader.hpp"
#include "Entity.hpp"
#include "Camera3D.hpp"
#include <vector>

class EntityRenderer {
public:


     void init();
     void renderEntities(Camera3D& camera);
     void destroy();

     std::vector<Entity> entities;

private:

     ModelShader m_shader;


};

#endif
