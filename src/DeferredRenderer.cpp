#include "DeferredRenderer.hpp"

void DeferredRenderer::init(Camera* cam){
    gbuffer.init(cam->width, cam->height);
    shader.init("res/shaders/deferred");
    shader.bind();
    shader.set("albedoTexture", 0);
    shader.set("specularTexture", 2);
    camera = cam;
}

void DeferredRenderer::draw(FObject* objects, int size){
    gbuffer.bind();
    shader.bind();
    shader.set("projection", camera->getProjection());
    shader.set("view", camera->getView());
    for(int i = 0; i < size; i++){
        shader.set("model", objects[i].transform.getMatrix());
        objects[i].texture.bind();
        objects[i].model.draw();
    }
    shader.unbind();
    gbuffer.unbind();
}

void DeferredRenderer::destroy(){
    shader.destroy();
    gbuffer.destroy();
}
