#pragma once

#include "glad.h"
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "InstanceRenderer.hpp"

class CascadeShadowMap {
public:
    void init(Camera* camera, Window* window);
    void generateShadowMap(const InstanceRenderer& renderer);
    void destroy();
    glm::mat4 getLightSpaceMatrix(const float nearPlane, const float farPlane);
    Camera* camera;
    Shader depthShader;
    Window* window;
    GLuint fbo;
    GLuint texture;
    glm::mat4 lightSpaceMatrices[3];
    float cascadeSplits[4];
};