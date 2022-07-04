#include "FEngine.hpp"

FEngine::FEngine(const char* title, int width, int height){
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
    camera.init(width, height, 70.0f);
}

void FEngine::draw(){
    inputManager.processInput();
}

FObject FEngine::loadObject(const std::string& path){
    return FObject(path + "/model.obj", path + "/albedo.jpg", path + "/normal.jpg", path + "/specular.jpg");
}
