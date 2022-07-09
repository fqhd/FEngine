#include "FEngine.hpp"

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f, 0.1, 450.0f);
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
    skybox.init();
    shadowMap.init(&camera, &window);
}

void FEngine::draw()
{
    window.clear();
    inputManager.processInput();

    shadowMap.generateShadowMap(objects.data(), objects.size());

    shader.bind();
    shader.set("projection", camera.getProjection());
    shader.set("view", camera.getView());
    shader.set("viewPos", camera.position);
    shader.set("farPlane", camera.far);
    shader.set("lightDir", camera.lightDirection);

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

    for (unsigned int i = 0; i < objects.size(); i++)
    {
        objects[i].texture.bind();
        shader.set("objectID", (int)i+1);
        shader.set("model", objects[i].transform.getMatrix());
        objects[i].model.draw();
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