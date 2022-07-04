#pragma once

#include "Fengine/Utils/Transform.hpp"
#include "Model.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"


class Entity {
public:

     Entity(const Transform& transform, Model* model, Texture* texture);

     void update();

     Transform transform;
     Model* model;
     Texture* texture;



private:



};
