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

    shader.set("lightSpaceMatrices[0]", shadowMap.lightSpaceMatrices[0]);
    shader.set("lightSpaceMatrices[1]", shadowMap.lightSpaceMatrices[1]);
    shader.set("lightSpaceMatrices[2]", shadowMap.lightSpaceMatrices[2]);
    shader.set("cascadePlaneDistances[0]", shadowMap.cascadeSplits[1]);
    shader.set("cascadePlaneDistances[1]", shadowMap.cascadeSplits[2]);
    shader.set("cascadePlaneDistances[2]", shadowMap.cascadeSplits[3]);

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