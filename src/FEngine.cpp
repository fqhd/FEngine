#include "FEngine.hpp"
#include <limits>

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f, 0.1, 450.0f);
    depthShader.init("./res/shaders/depth/vertex.glsl", "./res/shaders/depth/fragment.glsl");
    shader.init("./res/shaders/model/vertex.glsl", "./res/shaders/model/fragment.glsl");
    shader.bind();
    shader.set("texAlbedo", 0);
    shader.set("texNormal", 1);
    shader.set("texSpecular", 2);
    shader.set("gShadowMap[0]", 3);
    shader.set("gShadowMap[1]", 4);
    shader.set("gShadowMap[2]", 5);
    skybox.init();
    shadowMap.init();
    lightDirection = glm::normalize(glm::vec3(1.0));
    m_cascadeEnd[0] = camera.near;
    m_cascadeEnd[1] = 25.0f;
    m_cascadeEnd[2] = 100.0f;
    m_cascadeEnd[3] = camera.far;
}

glm::mat4 FEngine::getLightSpaceMatrix(const float nearPlane, const float farPlane)
{
    const auto proj = glm::perspective(
        glm::radians(camera.fov), camera.width / camera.height, nearPlane,
        farPlane);
    const glm::mat4 projview = proj * camera.getView();

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

    const auto lightView = glm::lookAt(center + lightDirection, center, glm::vec3(0.0f, 1.0f, 0.0f));

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

void FEngine::draw()
{
    window.clear();
    inputManager.processInput();

    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.fbo);
    glViewport(0, 0, 2048, 2048);

    glm::mat4 lightSpaceMatrices[3] = {
        getLightSpaceMatrix(m_cascadeEnd[0], m_cascadeEnd[1]),
        getLightSpaceMatrix(m_cascadeEnd[1], m_cascadeEnd[2]),
        getLightSpaceMatrix(m_cascadeEnd[2], m_cascadeEnd[3]),
    };

    for (int i = 0; i < 3; i++)
    {
        shadowMap.bindForWriting(i);
        glClear(GL_DEPTH_BUFFER_BIT);
        // Draw to depth texture
        depthShader.bind();
        depthShader.set("lightSpaceMatrix", lightSpaceMatrices[i]);
        for (unsigned int i = 0; i < objects.size(); i++)
        {
            depthShader.set("objectID", (int)i);
            depthShader.set("model", objects[i].transform.getMatrix());
            objects[i].model.draw();
        }
        depthShader.unbind();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glm::ivec2 size = window.getFramebufferSize();
    glViewport(0, 0, size.x, size.y);

    shader.bind();
    shader.set("projection", camera.getProjection());
    shader.set("view", camera.getView());
    shader.set("viewPos", camera.position);
    shader.set("farPlane", camera.far);
    shader.set("lightDir", lightDirection);

    // Upload light space matrices
    for (int i = 0; i < 3; i++)
    {
        shader.set("lightSpaceMatrices[" + std::to_string(i) + "]", lightSpaceMatrices[i]);
    }
    // Upload cascade plane distances
    for (int i = 0; i < 3; i++)
    {
        shader.set("cascadePlaneDistances[" + std::to_string(i) + "]", m_cascadeEnd[i + 1]);
    }

    // Bind the cascades
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, shadowMap.shadowMap[0]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, shadowMap.shadowMap[1]);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, shadowMap.shadowMap[2]);

    for (const auto &object : objects)
    {
        object.texture.bind();
        shader.set("model", object.transform.getMatrix());
        object.model.draw();
    }
    shader.unbind();
    skybox.render(camera.getProjection(), camera.getView());

    window.update();
}

FObject FEngine::loadObject(const std::string &path, Color color)
{
    return FObject(path + "/model.obj", path + "/albedo.jpg", path + "/normal.jpg", path + "/specular.jpg", color);
}

void FEngine::destroy()
{
    for (auto &object : objects)
    {
        object.model.destroy();
        object.texture.destroy();
    }
    shader.destroy();
    window.close();
}