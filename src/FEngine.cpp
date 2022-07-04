#include "FEngine.hpp"

FEngine::FEngine(const char* title, int width, int height){
    window.create(width, height, title);
    inputManager.init(window.getWindowPtr());
}

void FEngine::draw(){
    inputManager.processInput();
}