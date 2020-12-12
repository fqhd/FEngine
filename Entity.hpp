#ifndef ENTITY_H
#define ENTITY_H

#include "Transform.hpp"
#include "Model.hpp"
#include "Vertex.hpp"

class Entity {
public:

     Entity(){}
     Entity(const Transform& t, Model* m, StaticColor c);
     ~Entity(){}

     void update();
     void render();

     Transform transform;
     Model* model;
     StaticColor color;



private:



};

#endif
