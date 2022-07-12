#include "FEngine.hpp"

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f, 0.1, 350.0f);
    masterRenderer.init(&camera, &window);
    deferredRenderer.init(&camera, &window);
}

void FEngine::draw()
{
    window.clear();
    inputManager.processInput();
    camera.update();

    deferredRenderer.draw(objects.data(), objects.size());

    masterRenderer.drawObjects(objects.data(), objects.size(), deferredRenderer);

    window.update();
}

FObject FEngine::loadObject(const std::string &path, Color color)
{
    return FObject(path + "/model.obj", path + "/albedo.jpg", path + "/normal.jpg", path + "/specular.jpg", color);
}

void FEngine::destroy()
{
    masterRenderer.destroy();
    deferredRenderer.destroy();
    for (auto &object : objects)
    {
        object.model.destroy();
        object.texture.destroy();
    }
    window.close();
}