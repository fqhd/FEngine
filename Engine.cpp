#include "Engine.hpp"

void Engine::init(Settings& settings){
     assets.init();
     camera3D.init(settings.screenWidth, settings.screenHeight);
     camera2D.init(settings.screenWidth, settings.screenHeight);
     masterRenderer.init(settings);
}

void Engine::update(InputManager& manager, Settings& settings){
     camera3D.move(manager, settings, 0.025);
     updateGUI(manager);
}

void Engine::render(std::vector<Entity>& entities){
     masterRenderer.renderScene(entities, camera3D, assets);
     masterRenderer.renderGUI(gui, camera2D);
}

void Engine::updateGUI(InputManager& manager){
     for(auto& i : gui.buttons) i.update(manager);
}

void Engine::destroy(){
     masterRenderer.destroy();
}
