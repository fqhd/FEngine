#include "Engine.hpp"

void Engine::init(Settings& settings){
     assets.init();
     camera3D.init(settings.screenWidth, settings.screenHeight);
     camera2D.init(settings.screenWidth, settings.screenHeight);
     masterRenderer.init(settings);
}

void Engine::update(Settings& settings){
     camera3D.move(settings);
     updateGUI();
}

void Engine::render(std::vector<Entity>& entities){
     masterRenderer.renderScene(entities, camera3D, assets);
     masterRenderer.renderGUI(gui, camera2D);
}

void Engine::updateGUI(){
     for(auto& i : gui.buttons) i.update();
}

void Engine::destroy(){
     masterRenderer.destroy();
}
