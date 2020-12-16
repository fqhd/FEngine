#include "Engine.hpp"

void Engine::init(unsigned int screenWidth, unsigned int screenHeight, const std::string& name){

     window.create(screenWidth, screenHeight, name.c_str());
     InputManager::init(window.window);
     assets.init();
     camera3D.init(screenWidth, screenHeight);
     camera2D.init(screenWidth, screenHeight);
     masterRenderer.init(screenWidth, screenHeight);

}

void Engine::processInput(){
     window.m_closeRequested = InputManager::processInput(window.window);
}

void Engine::update(){
     camera3D.move();
     updateGUI();
}

void Engine::render(){
     window.clear();


     window.update();
}

void Engine::updateGUI(){
     for(auto& i : gui.buttons) i.update();
}

void Engine::destroy(){
     masterRenderer.destroy();
     window.close();
}
