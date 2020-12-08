#include "Engine.hpp"

void Engine::init(Settings& settings){
     assets.init();
     camera.init(settings.screenWidth, settings.screenHeight);
     cubemap.init();
     masterRenderer.init(settings);
}

void Engine::update(InputManager& manager, Settings& settings){
     camera.move(manager, settings);
     cubemap.update();
}

void Engine::render(std::vector<Entity>& entities){
     cubemap.render(camera, assets);
     masterRenderer.renderScene(entities, camera);
}

void Engine::destroy(){
     cubemap.destroy();
     masterRenderer.destroy();
}
