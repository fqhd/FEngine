#pragma once
#include "Model.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

class FObject {
public:
    FObject(const std::string& modelPath, const std::string& albedoPath, const std::string& normalPath, const std::string& specularPath){
        model.init(modelPath);
        texture.init(albedoPath, normalPath, specularPath);
    }
    Texture texture;
    Model model;
    Transform transform;
};