#include "CascadeShadowMap.hpp"
#include <limits>
#include <iostream>
#include <vector>

void CascadeShadowMap::init(Camera *cam, Window* win)
{
    window = win;
    camera = cam;
    depthShader.init("./res/shaders/depth/vertex.glsl", "./res/shaders/depth/fragment.glsl");
    glGenFramebuffers(1, &fbo);

    // Create the depth buffer
    glGenTextures(3, shadowMap);
    glGenTextures(3, IDTexture);
    int width = 4096;
    for (int i = 0; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, shadowMap[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, width, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        cascadeSplits[0] = camera->near;
        cascadeSplits[1] = 25.0f;
        cascadeSplits[2] = 100.0f;
        cascadeSplits[3] = camera->far;
        width /= 2;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap[0], 0);
    width = 4096;
    for (int i = 0; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, IDTexture[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, width, width, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        width /= 2;
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, IDTexture[0], 0);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FB error, status: 0x" << Status << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CascadeShadowMap::bindForWriting(int index)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap[index], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, IDTexture[index], 0);
}

void CascadeShadowMap::bindForReading()
{
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, shadowMap[0]);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, shadowMap[1]);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, shadowMap[2]);

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, IDTexture[0]);

    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, IDTexture[1]);

    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, IDTexture[2]);
}

void CascadeShadowMap::generateShadowMap(FObject *objects, int size)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    lightSpaceMatrices[0] = getLightSpaceMatrix(cascadeSplits[0], cascadeSplits[1]);
    lightSpaceMatrices[1] = getLightSpaceMatrix(cascadeSplits[1], cascadeSplits[2]);
    lightSpaceMatrices[2] = getLightSpaceMatrix(cascadeSplits[2], cascadeSplits[3]);

    int width = 4096;
    for (int i = 0; i < 3; i++)
    {
        glViewport(0, 0, width, width);
        bindForWriting(i);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        // Draw to depth texture
        depthShader.bind();
        depthShader.set("lightSpaceMatrix", lightSpaceMatrices[i]);
        glCullFace(GL_FRONT);
        for (int i = 0; i < size; i++)
        {
            depthShader.set("objectID", (int)i + 1);
            depthShader.set("model", objects[i].transform.getMatrix());
            objects[i].model.draw();
        }
        glCullFace(GL_BACK);
        depthShader.unbind();
        width /= 2;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glm::ivec2 windowSize = window->getFramebufferSize();
    glViewport(0, 0, windowSize.x, windowSize.y);
}

glm::mat4 CascadeShadowMap::getLightSpaceMatrix(const float nearPlane, const float farPlane)
{
    const auto proj = glm::perspective(
        glm::radians(camera->fov), camera->width / camera->height, nearPlane,
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
    constexpr float zMult = 10.0f;
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

void CascadeShadowMap::destroy(){
    depthShader.destroy();
    glDeleteTextures(3, shadowMap);
    glDeleteTextures(3, IDTexture);
    glDeleteFramebuffers(1, &fbo);
}