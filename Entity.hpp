#ifndef ENTITY_H
#define ENTITY_H

#include "Transform.hpp"
#include "Model.hpp"
#include "Vertex.hpp"

class Entity {
public:

     Entity(const Transform& t, Model* m, StaticColor c);

     void render();

     Transform transform;
     Model* model;
     StaticColor color;

private:



};

#endif
