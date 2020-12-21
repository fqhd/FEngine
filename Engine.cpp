#include "Engine.hpp"

void Engine::init(unsigned int width, unsigned int height, const std::string& name, bool resizable, bool decorated){

     //Engine Inits
     window.create(width, height, name, resizable, decorated);
     renderer.init(width, height);
     camera.firstPersonCamera.init(width, height, glm::vec3(0, 0, 0));
     camera.thirdPersonCamera.init(width, height, glm::vec3(0, 0, 0), glm::vec3(10, 10, 10));
     assets.init();

     //Game Variables
     entities.emplace_back(Transform(glm::vec3(0, 0, 0), glm::vec3(50, 50, 50), glm::vec3(1, 1, 1)), assets.getPlayerModel(), assets.getPlayerTexture());

     camera.setMode(window.window, CameraMode::THIRD_PERSON);


}

void Engine::update(){
     camera.firstPersonCamera.update(0.001f);
     camera.thirdPersonCamera.update();
}

void Engine::render(){
     window.clear();

     renderer.renderScene(entities, camera);

     window.update();
}

void Engine::destroy(){
     renderer.destroy();
     window.close();
}
