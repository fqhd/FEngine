#include "Engine.hpp"

void Engine::init(Settings& settings){
     assets.init();
     camera.init(settings.screenWidth, settings.screenHeight);
     masterRenderer.init(settings);
}

void Engine::update(InputManager& manager, Settings& settings){
     camera.move(manager, settings);
}

void Engine::render(std::vector<Entity>& entities){
     masterRenderer.renderScene(entities, camera, assets);
}

void Engine::destroy(){
     masterRenderer.destroy();
}
