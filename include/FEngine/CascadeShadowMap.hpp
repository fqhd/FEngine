#pragma once

#include "glad.h"
#include <glm/glm.hpp>
#include <FEngine/Camera.hpp>
#include <FEngine/FObject.hpp>
#include <FEngine/Window.hpp>
#include <FEngine/Shader.hpp>

class CascadeShadowMap {
public:
    void init(Camera* camera, Window* window);
    void generateShadowMap(FObject* objects, int size);
    void destroy();
    glm::mat4 getLightSpaceMatrix(const float nearPlane, const float farPlane);
    Camera* camera;
    Shader depthShader;
    Window* window;
    GLuint fbo;
    GLuint texture;
    GLuint idtexture;
    glm::mat4 lightSpaceMatrices[3];
    float cascadeSplits[4];
};