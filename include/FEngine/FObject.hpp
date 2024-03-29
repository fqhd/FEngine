#pragma once
#include <FEngine/Model.hpp>
#include <FEngine/Texture.hpp>
#include <FEngine/Transform.hpp>
#include <iostream>

namespace FEngine
{
    class FObject
    {
    public:
        FObject() {}
        FObject(const std::string &modelPath, const std::string &albedoPath, const std::string &ambientPath, Color color)
        {
            model.init(modelPath);
            texture.init(albedoPath, ambientPath, color);
        }
        Texture texture;
        Model model;
        Transform transform;
    };
}