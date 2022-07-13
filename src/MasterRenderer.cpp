#include "MasterRenderer.hpp"

void MasterRenderer::init(Camera *cam, Window *window)
{
    camera = cam;
    shader.init("./res/shaders/model");
    shader.bind();
    shader.set("texAlbedo", 0);
    shader.set("texNormal", 1);
    shader.set("texPosition", 2);
    shader.set("gShadowMap", 3);
    shader.set("ssaoTexture", 4);
    shader.set("depthTexture", 5);
    shadowMap.init(camera, window);
    quad.init();
    ssao.init(window);
    ssaoBlur.init(window);
}

void MasterRenderer::drawObjects(FObject *objects, int size, DeferredRenderer& renderer)
{
    shadowMap.generateShadowMap(objects, size);
    ssao.draw(renderer, camera);
    ssaoBlur.draw(ssao.textureID);
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
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.albedoTextureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.normalTextureID);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.positionTextureID);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMap.texture);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, ssaoBlur.textureID);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.depthTexture);
    quad.draw();
    shader.unbind();
}

void MasterRenderer::destroy(){
    shadowMap.destroy();
    shader.destroy();
    ssaoBlur.destroy();
    ssao.destroy();
    quad.destroy();
}