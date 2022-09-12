#include <FEngine/FEngine.hpp>

FEngine::FEngine(const char *title, int width, int height)
{
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f, 0.1, 350.0f);
    masterRenderer.init(&camera, &window);
    fpCam = false;
    timer.restart();
    deltaTime = 0.0f;
}

void FEngine::draw(const FObject& object)
{
    objects.push_back(object);
}

void FEngine::firstPersonInput(float deltaTime){
    glm::vec3 f = camera.getForward();
    glm::vec3 forward = glm::normalize(glm::vec3(f.x, 0.0f, f.z));
    glm::vec3 side = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    if(inputManager.isKeyDown(GLFW_KEY_W)){
        camera.position += camera.speed * deltaTime * forward;
    }
    if(inputManager.isKeyDown(GLFW_KEY_A)){
        camera.position -= camera.speed * deltaTime * side;
    }
    if(inputManager.isKeyDown(GLFW_KEY_S)){
        camera.position -= camera.speed * deltaTime * forward;
    }
    if(inputManager.isKeyDown(GLFW_KEY_D)){
        camera.position += camera.speed * deltaTime * side;
    }
    if(inputManager.isKeyDown(GLFW_KEY_LEFT_SHIFT)){
        camera.position.y -= camera.speed * deltaTime;
    }
    if(inputManager.isKeyDown(GLFW_KEY_SPACE)){
        camera.position.y += camera.speed * deltaTime;
    }
    camera.yaw -= inputManager.getDeltaMousePos().x * camera.mouseSensitivity;
    camera.pitch -= inputManager.getDeltaMousePos().y * camera.mouseSensitivity;
    if(camera.pitch >= 89.9f){
        camera.pitch = 89.9f;
    }
    if(camera.pitch <= -89.9f){
        camera.pitch = -89.9f;
    }
}

void FEngine::update(){
    window.clear();
    inputManager.processInput();
    deltaTime = timer.restart();
    
    camera.update();

    if(fpCam) firstPersonInput(deltaTime);

    masterRenderer.drawObjects(objects.data(), objects.size());

    window.update();
    objects.clear();
}

void FEngine::firstPersonCamera(bool enabled){
    fpCam = enabled;
    window.setMouseGrabbed(enabled);
}

FObject FEngine::loadObject(const std::string &path, Color color)
{
    auto it = map.find(path);
    if(it != map.end()){
        return it->second;
    }
    const FObject obj = FObject(path + "/model.obj", path + "/ambient.png", path + "/albedo.png", color);
    map[path] = obj;
    return obj;
}

float FEngine::getDeltaTime(){
    return deltaTime;
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