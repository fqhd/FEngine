#pragma once
#include "Model.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

class FObject {
public:
    FObject(Model m, Texture t){
        model = m;
        texture = t;
    }
    Texture texture;
    Model model;
    Transform transform;
};