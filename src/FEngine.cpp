#include "FEngine.hpp"

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f);
    shader.init("./res/shaders/modelShader/vertex.glsl", "./res/shaders/modelShader/fragment.glsl");
}

void FEngine::draw(const FObject *objects, int numEntities)
{
    window.clear();

    shader.bind();
    shader.set("projection", camera.getProjection());
    shader.set("view", camera.getView());
    for (int i = 0; i < numEntities; i++)
    {
        shader.set("model", objects[i].transform.getMatrix());
        objects[i].model.draw();
    }
    shader.unbind();
    inputManager.processInput();

    window.update();
}

FObject FEngine::loadObject(const std::string &path)
{
    return FObject(path + "/model.obj", path + "/albedo.jpg", path + "/normal.jpg", path + "/specular.jpg");
}
