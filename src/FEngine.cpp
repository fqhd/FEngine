#include <FEngine/FEngine.hpp>

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f, 0.1, 350.0f);
    masterRenderer.init(&camera, &window);
}

void FEngine::draw(const FObject& object)
{
    objects.push_back(object);
}

void FEngine::update(){
    window.clear();
    inputManager.processInput();
    camera.update();

    masterRenderer.drawObjects(objects.data(), objects.size());

    window.update();
    objects.clear();
}

FObject FEngine::getObject(const std::string &path, Color color)
{
    auto it = map.find(path);
    if(it != map.end()){
        return it->second;
    }
    const FObject obj = FObject(path + "/model.obj", path + "/albedo.jpg", color);
    map[path] = obj;
    return obj;
}

void FEngine::destroy()
{
    masterRenderer.destroy();
    for (auto &object : objects)
    {
        object.model.destroy();
        object.texture.destroy();
    }
    window.close();
}