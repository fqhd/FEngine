#ifndef ENTITY_HANDLER_H
#define ENTITY_HANDLER_H

#include "StaticShader.hpp"
#include "Entity.hpp"
#include "Camera3D.hpp"
#include "Assets.hpp"
#include <vector>

class EntityHandler {
public:

     void updateEntities();

     std::vector<Entity> entities;

private:


};

#endif
