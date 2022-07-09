#include "FEngine.hpp"

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f, 0.1, 450.0f);
    modelRenderer.init(&camera, &window);
    skybox.init();
}

void FEngine::draw()
{
    window.clear();
    inputManager.processInput();

    modelRenderer.drawObjects(objects.data(), objects.size());

    skybox.render(camera.getProjection(), camera.getView());

    window.update();
}

FObject FEngine::loadObject(const std::string &path, Color color)
{
    return FObject(path + "/model.obj", path + "/albedo.jpg", path + "/normal.jpg", path + "/specular.jpg", color);
}

void FEngine::destroy()
{
    skybox.destroy();
    modelRenderer.destroy();
    for (auto &object : objects)
    {
        object.model.destroy();
        object.texture.destroy();
    }
    window.close();
}