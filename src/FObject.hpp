#pragma once
#include "Model.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

struct FObject {
    Texture texture;
    Model model;
    Transform transform;
};
