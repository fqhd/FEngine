#include "ModelRenderer.hpp"

void ModelRenderer::init(Camera *cam, Window *window)
{
    camera = cam;
    shader.init("./res/shaders/model/vertex.glsl", "./res/shaders/model/fragment.glsl");
    shader.bind();
    shader.set("texAlbedo", 0);
    shader.set("texNormal", 1);
    shader.set("texSpecular", 2);
    shader.set("gShadowMap[0]", 3);
    shader.set("gShadowMap[1]", 4);
    shader.set("gShadowMap[2]", 5);
    shader.set("idTexture[0]", 6);
    shader.set("idTexture[1]", 7);
    shader.set("idTexture[2]", 8);
    shadowMap.init(camera, window);
}

void ModelRenderer::drawObjects(FObject *objects, int size)
{
    shadowMap.generateShadowMap(objects, size);
    shader.bind();
    shader.set("projection", camera->getProjection());
    shader.set("view", camera->getView());
    shader.set("viewPos", camera->position);
    shader.set("farPlane", camera->far);
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
    shadowMap.bindForReading();

    for (unsigned int i = 0; i < size; i++)
    {
        objects[i].texture.bind();
        shader.set("objectID", (int)i + 1);
        shader.set("model", objects[i].transform.getMatrix());
        objects[i].model.draw();
    }
    shader.unbind();
}

void ModelRenderer::destroy(){
    shadowMap.destroy();
    shader.destroy();
}