#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "FObject.h"
#include "Window.hpp"
#include "Shader.hpp"

class CascadeShadowMap {
public:
    void init(Camera* camera, Window* window);
    void generateShadowMap(FObject* objects, int size);
    void bindForReading();
    void bindForWriting(int index);
    void destroy();
    glm::mat4 getLightSpaceMatrix(const float nearPlane, const float farPlane);
    Camera* camera;
    Shader depthShader;
    Window* window;
    GLuint fbo;
    GLuint shadowMap[3];
    GLuint IDTexture[3];
    glm::mat4 lightSpaceMatrices[3];
    float cascadeSplits[4];
};