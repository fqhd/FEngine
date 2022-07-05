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
}

void FEngine::draw()
{
    window.clear();

    shader.bind();
    shader.set("projection", camera.getProjection());
    shader.set("view", camera.getView());
    for (const auto& object : objects)
    {
        object.texture.bind();
        shader.set("model", object.transform.getMatrix());
        object.model.draw();
    }
    shader.unbind();
    inputManager.processInput();

    window.update();
}

FObject FEngine::loadObject(const std::string &path)
{
    return FObject(path + "/model.obj", path + "/albedo.jpg", path + "/normal.jpg", path + "/specular.jpg");
}

void FEngine::destroy(){
    for(auto& object : objects){
        object.model.destroy();
        object.texture.destroy();
    }
    shader.destroy();
    window.close();
}