#include "CascadeShadowMap.hpp"
#include <limits>
#include <iostream>
#include <vector>

void CascadeShadowMap::init(Camera *cam, Window *win)
{
    window = win;
    camera = cam;
    depthShader.init("./res/shaders/depth");
    glGenFramebuffers(1, &fbo);

    // Create the depth buffer
    glGenTextures(1, &texture);
    const int width = 4096;
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    glTexImage3D(
        GL_TEXTURE_2D_ARRAY,
        0,
        GL_DEPTH_COMPONENT,
        width,
        width,
        3,
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        nullptr);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    const float bordercolor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, bordercolor);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);

    // Disable color read/write
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
        throw 0;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    cascadeSplits[0] = camera->near;
    cascadeSplits[1] = 10.0f;
    cascadeSplits[2] = 45.0f;
    cascadeSplits[3] = camera->far / 2.0;
}

void CascadeShadowMap::generateShadowMap(FObject *objects, int size)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    lightSpaceMatrices[0] = getLightSpaceMatrix(cascadeSplits[0], cascadeSplits[1]);
    lightSpaceMatrices[1] = getLightSpaceMatrix(cascadeSplits[1], cascadeSplits[2]);
    lightSpaceMatrices[2] = getLightSpaceMatrix(cascadeSplits[2], cascadeSplits[3]);

    int width = 4096;
    glViewport(0, 0, width, width);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Draw to depth texture
    depthShader.bind();
    // Upload 3 light space matrices
    for(int i = 0; i < 3; i++){
        depthShader.set("lightSpaceMatrices[" + std::to_string(i) + "]", lightSpaceMatrices[i]);
    }

    for (int i = 0; i < size; i++)
    {
        depthShader.set("model", objects[i].transform.getMatrix());
        objects[i].model.draw();
    }
    depthShader.unbind();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glm::ivec2 windowSize = window->getFramebufferSize();
    glViewport(0, 0, windowSize.x, windowSize.y);
}

glm::mat4 CascadeShadowMap::getLightSpaceMatrix(const float nearPlane, const float farPlane)
{
    const auto proj = glm::perspective(
        glm::radians(camera->fov), camera->ar, nearPlane,
        farPlane);

    const glm::mat4 projview = proj * camera->getView();

    std::vector<glm::vec4> corners;
    const auto inv = glm::inverse(projview);
    for (unsigned int x = 0; x < 2; ++x)
    {
        for (unsigned int y = 0; y < 2; ++y)
        {
            for (unsigned int z = 0; z < 2; ++z)
            {
                const glm::vec4 pt = inv * glm::vec4(2.0f * x - 1.0f, 2.0f * y - 1.0f, 2.0f * z - 1.0f, 1.0f);
                corners.push_back(pt / pt.w);
            }
        }
    }

    glm::vec3 center = glm::vec3(0, 0, 0);
    for (const auto &v : corners)
    {
        center += glm::vec3(v);
    }
    center /= corners.size();

    const auto lightView = glm::lookAt(center + camera->lightDirection, center, glm::vec3(0.0f, 1.0f, 0.0f));

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::min();
    float minZ = std::numeric_limits<float>::max();
    float maxZ = std::numeric_limits<float>::min();
    for (const auto &v : corners)
    {
        const auto trf = lightView * v;
        minX = std::min(minX, trf.x);
        maxX = std::max(maxX, trf.x);
        minY = std::min(minY, trf.y);
        maxY = std::max(maxY, trf.y);
        minZ = std::min(minZ, trf.z);
        maxZ = std::max(maxZ, trf.z);
    }

    // Tune this parameter according to the scene
    const float zMult = 10.0f;
    if (minZ < 0)
    {
        minZ *= zMult;
    }
    else
    {
        minZ /= zMult;
    }
    if (maxZ < 0)
    {
        maxZ /= zMult;
    }
    else
    {
        maxZ *= zMult;
    }

    const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);

    return lightProjection * lightView;
}

void CascadeShadowMap::destroy()
{
    depthShader.destroy();
    glDeleteTextures(1, &texture);
    glDeleteFramebuffers(1, &fbo);
}