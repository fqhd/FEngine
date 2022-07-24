#include "MasterRenderer.hpp"

void MasterRenderer::init(Camera *cam, Window *window)
{
    camera = cam;
    shader.init("../res/shaders/model");
    shader.bind();
    shader.set("gShadowMap", 0);
    shadowMap.init(camera, window);
    fxaa.init(window);
    skybox.init();
    instanceRenderer.init();
}

void MasterRenderer::drawObjects()
{
    instanceRenderer.end();
    shadowMap.generateShadowMap(instanceRenderer);
    fxaa.bind();
    shader.bind();
    shader.set("projection", camera->getProjection());
    shader.set("view", camera->getView());
    shader.set("lightDir", camera->lightDirection);

    // Upload light space matrices
    for (int i = 0; i < 3; i++)
    {
        shader.set("lightSpaceMatrices[" + std::to_string(i) + "]", shadowMap.lightSpaceMatrices[i]);
    }
    // Upload cascade plane distances
    for (int i = 0; i < 3; i++)
    {
        shader.set("cascadePlaneDistances[" + std::to_string(i) + "]", shadowMap.cascadeSplits[i + 1]);
    }

    // Bind the cascades
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMap.texture);
    instanceRenderer.draw();
    shader.unbind();
    skybox.render(camera->getProjection(), camera->getView());
    fxaa.unbind();
    
    fxaa.drawWithFXAA();
    instanceRenderer.begin();
}

void MasterRenderer::destroy(){
    skybox.destroy();
    shadowMap.destroy();
    shader.destroy();
    fxaa.destroy();
}