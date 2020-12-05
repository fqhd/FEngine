#ifndef ENTITY_H
#define ENTITY_H

#include "Transform.hpp"
#include "Model.hpp"

class Entity {
public:

     void Entity(const Transform& t, Model* m);

     void render();

     Transform transform;
     Model* model;

private:



};

#endif
