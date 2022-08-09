#include <FEngine/MasterRenderer.hpp>

#define LOAD_AS_STRING(...) "#version 330 core \n"#__VA_ARGS__

void MasterRenderer::init(Camera *cam, Window *window)
{
    camera = cam;
    shader.init(
        #include <FEngine/shaders/model/vertex.glsl>
        ,
        #include <FEngine/shaders/model/fragment.glsl>
    );
    
    shader.bind();
    shader.set("albedoTexture", 0);
    shader.set("ambientTexture", 1);
    shader.set("gShadowMap", 2);
    shadowMap.init(camera, window);
    skybox.init();
}

void MasterRenderer::drawObjects(FObject *objects, int size)
{
    shadowMap.generateShadowMap(objects, size);
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
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMap.texture);

    // Draw the models
    for(int i = 0; i < size; i++){
        shader.set("model", objects[i].transform.getMatrix());
        objects[i].texture.bind();
        objects[i].model.draw();
    }

    shader.unbind();
    skybox.render(camera->getProjection(), camera->getView());
}

void MasterRenderer::destroy(){
    skybox.destroy();
    shadowMap.destroy();
    shader.destroy();
}