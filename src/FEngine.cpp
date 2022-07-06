#include "FEngine.hpp"
#include <limits>

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f);
    depthShader.init("./res/shaders/depth/vertex.glsl", "./res/shaders/depth/fragment.glsl");
    shader.init("./res/shaders/model/vertex.glsl", "./res/shaders/model/fragment.glsl");
    shader.set("texAlbedo", 0);
    shader.set("texNormal", 1);
    shader.set("texSpecular", 2);
    shader.set("cascade1", 3);
    shader.set("cascade2", 4);
    shader.set("cascade3", 5);
    skybox.init();
    debugShader.init("./res/shaders/quad/vertex.glsl", "./res/shaders/quad/fragment.glsl");
    quad.init();
    shadowMap.init();
    lightDirection = glm::normalize(glm::vec3(-1.0));
    m_cascadeEnd[0] = 0.1;
    m_cascadeEnd[1] = 45.0f,
    m_cascadeEnd[2] = 120.0f,
    m_cascadeEnd[3] = 250.0;
}

void FEngine::draw()
{
    window.clear();
    inputManager.processInput();

    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.fbo);
    glViewport(0, 0, 1024, 1024);

    // Get lightSpaceMatrices
    glm::mat4 lightSpaceMatrices[3];
    glm::mat4 CamInv = glm::inverse(camera.getView());
    glm::mat4 LightM = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), lightDirection, glm::vec3(0.0, 1.0, 0.0));

    float ar = 800.0f / 600.0f;
    float tanHalfHFOV = tanf(glm::radians(camera.fov / 2.0f));
    float tanHalfVFOV = tanf(glm::radians((camera.fov * ar) / 2.0f));

    for (int i = 0; i < 3; i++)
    {
        float xn = m_cascadeEnd[i] * tanHalfHFOV;
        float xf = m_cascadeEnd[i + 1] * tanHalfHFOV;
        float yn = m_cascadeEnd[i] * tanHalfVFOV;
        float yf = m_cascadeEnd[i + 1] * tanHalfVFOV;

        glm::vec4 frustumCorners[8] = {
            // near face
            glm::vec4(xn, yn, m_cascadeEnd[i], 1.0),
            glm::vec4(-xn, yn, m_cascadeEnd[i], 1.0),
            glm::vec4(xn, -yn, m_cascadeEnd[i], 1.0),
            glm::vec4(-xn, -yn, m_cascadeEnd[i], 1.0),

            // far face
            glm::vec4(xf, yf, m_cascadeEnd[i + 1], 1.0),
            glm::vec4(-xf, yf, m_cascadeEnd[i + 1], 1.0),
            glm::vec4(xf, -yf, m_cascadeEnd[i + 1], 1.0),
            glm::vec4(-xf, -yf, m_cascadeEnd[i + 1], 1.0)};
        glm::vec4 frustumCornersL[8];

        float minX = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::min();
        float minY = std::numeric_limits<float>::max();
        float maxY = std::numeric_limits<float>::min();
        float minZ = std::numeric_limits<float>::max();
        float maxZ = std::numeric_limits<float>::min();

        for (int j = 0 ; j < 8 ; j++) {

            // Transform the frustum coordinate from view to world space
            glm::vec4 vW = CamInv * frustumCorners[j];

            // Transform the frustum coordinate from world to light space
            frustumCornersL[j] = LightM * vW;

            minX = std::min(minX, frustumCornersL[j].x);
            maxX = std::max(maxX, frustumCornersL[j].x);
            minY = std::min(minY, frustumCornersL[j].y);
            maxY = std::max(maxY, frustumCornersL[j].y);
            minZ = std::min(minZ, frustumCornersL[j].z);
            maxZ = std::max(maxZ, frustumCornersL[j].z);
        }
        lightSpaceMatrices[i] = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ) * LightM;
    }

    for (int i = 0; i < 3; i++)
    {
        shadowMap.bindForWriting(i);
        glClear(GL_DEPTH_BUFFER_BIT);
        // Draw to depth texture
        depthShader.bind();
        depthShader.set("lightSpaceMatrix", lightSpaceMatrices[i]);
        for (const auto &object : objects)
        {
            depthShader.set("model", object.transform.getMatrix());
            object.model.draw();
        }
        depthShader.unbind();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 1024, 1024);

    shader.bind();
    shader.set("projection", camera.getProjection());
    shader.set("view", camera.getView());
    for (const auto &object : objects)
    {
        object.texture.bind();
        shader.set("model", object.transform.getMatrix());
        object.model.draw();
    }
    shader.unbind();

    skybox.render(camera.getProjection(), camera.getView());

    debugShader.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowMap.shadowMap[2]);
    glDisable(GL_CULL_FACE);
    quad.draw();
    glEnable(GL_CULL_FACE);
    debugShader.unbind();

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