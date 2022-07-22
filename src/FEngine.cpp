#include "FEngine.hpp"

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f, 0.1, 350.0f);
    masterRenderer.init(&camera, &window);
}

void FEngine::draw()
{
    window.clear();
    inputManager.processInput();
    camera.update();

    masterRenderer.drawObjects();

    window.update();
}

void FEngine::destroy()
{
    masterRenderer.destroy();
    window.close();
}