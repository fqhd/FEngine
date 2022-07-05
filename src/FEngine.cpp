#include "FEngine.hpp"

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f);
    shader.init("./res/shaders/modelShader/vertex.glsl", "./res/shaders/modelShader/fragment.glsl");
    shader.set("texAlbedo", 0);
    shader.set("texNormal", 1);
    shader.set("texSpecular", 2);
    textureManager.init();
}

void FEngine::draw()
{
    window.clear();

    shader.bind();
    shader.set("projection", camera.getProjection());
    shader.set("view", camera.getView());
    for (const auto& object : objects)
    {
        textureManager.bindTexture(object.texture);
        shader.set("model", object.transform.getMatrix());
        object.model.draw();
    }
    shader.unbind();
    inputManager.processInput();

    window.update();
}

FObject FEngine::loadObject(const std::string &path)
{
    FObject object;
    object.texture = textureManager.loadTexture(path + "/albedo.jpg", path + "/normal.jpg", path + "/specular.jpg");
    object.model.init(path + "/model.obj");
    return object;
}

void FEngine::destroy(){
    for(auto& object : objects){
        object.model.destroy();
        textureManager.destroyTexture(object.texture);
    }
    shader.destroy();
    window.close();
}