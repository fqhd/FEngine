#include "MasterRenderer.hpp"

void MasterRenderer::init(Camera *cam, Window *window)
{
    camera = cam;
    shader.init("./res/shaders/model");
    shader.bind();
    shader.set("texAlbedo", 0);
    shader.set("texNormal", 1);
    shader.set("texPosition", 2);
    shader.set("gShadowMap[0]", 3);
    shader.set("gShadowMap[1]", 4);
    shader.set("gShadowMap[2]", 5);
    shader.set("idTexture[0]", 6);
    shader.set("idTexture[1]", 7);
    shader.set("idTexture[2]", 8);
    shadowMap.init(camera, window);
    quad.init();
}

void MasterRenderer::drawObjects(FObject *objects, int size, DeferredRenderer& renderer)
{
    shadowMap.generateShadowMap(objects, size);
    shader.bind();
    // shader.set("projection", camera->getProjection());
    // shader.set("view", camera->getView());
    // shader.set("viewPos", camera->position);
    // shader.set("farPlane", camera->far);
    // shader.set("lightDir", camera->lightDirection);

    // // Upload light space matrices
    // for (int i = 0; i < 3; i++)
    // {
    //     shader.set("lightSpaceMatrices[" + std::to_string(i) + "]", shadowMap.lightSpaceMatrices[i]);
    // }
    // // Upload cascade plane distances
    // for (int i = 0; i < 3; i++)
    // {
    //     shader.set("cascadePlaneDistances[" + std::to_string(i) + "]", shadowMap.cascadeSplits[i + 1]);
    // }

    // // Bind the cascades
    // shadowMap.bindForReading();

    // for (unsigned int i = 0; i < size; i++)
    // {
    //     shader.set("objectID", (int)i + 1);
    //     shader.set("model", objects[i].transform.getMatrix());
    //     objects[i].model.draw();
    // }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.albedoTextureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.normalTextureID);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.positionTextureID);
    quad.draw();
    shader.unbind();
}

void MasterRenderer::destroy(){
    shadowMap.destroy();
    shader.destroy();
}