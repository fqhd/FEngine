#pragma once
#include <FEngine/Model.hpp>
#include <FEngine/Texture.hpp>
#include <FEngine/Transform.hpp>
#include <iostream>

class FObject {
public:
    FObject(){}
    FObject(const std::string& modelPath, const std::string& albedoPath, const std::string& normalPath, const std::string& specularPath, Color color){
        model.init(modelPath);
        texture.init(albedoPath, normalPath, specularPath, color);
    }
    Texture texture;
    Model model;
    Transform transform;
};