#include "Engine.hpp"

void Engine::init(unsigned int width, unsigned int height, const std::string& name, bool resizable, bool decorated){

     //Engine Inits
     window.create(width, height, name, resizable, decorated);
     m_ssao.init(width, height);
     m_skybox.init("res/textures/sky/", "res/textures/sky/");
     m_dynamicEntityRenderer.init();
     //m_staticTerrain.init(assets.getGrassTexture(), "res/textures/heightmap.png", 1, 64.0f, 32.0f, 16.0f);
     m_dynamicTerrain.init(64);
     camera.firstPersonCamera.init(width, height, glm::vec3(0, 0, 0));
     camera.thirdPersonCamera.init(width, height, glm::vec3(0, 0, 0), glm::vec3(10, 10, 10));
     camera.thirdPersonCamera.center = glm::vec3(16, 2.5, 16);
     camera.firstPersonCamera.speed = 256.0f;
     assets.init();

     //Game Variables
     //entities.emplace_back(Transform(glm::vec3(0, 0, 0), glm::vec3(50, 50, 50), glm::vec3(1, 1, 1)), assets.getPlayerModel(), assets.getPlayerTexture());
     //entities.emplace_back(Transform(glm::vec3(2, 0, 0), glm::vec3(50, 50, 50), glm::vec3(1, 1, 1)), assets.getPlayerModel(), assets.getPlayerTexture());

     camera.setMode(window.window, CameraMode::FIRST_PERSON);


}

void Engine::update(){
     camera.firstPersonCamera.update(0.001f);
     camera.thirdPersonCamera.update();
     m_dynamicTerrain.update(camera);
}

void Engine::render(){
     window.clear();

     m_ssao.bind();

     m_dynamicEntityRenderer.render(entities, camera);
     m_skybox.render(camera);
     m_dynamicTerrain.render(camera);

     m_ssao.unbind();


     m_ssao.render(camera);

     window.update();
}

void Engine::destroy(){
     m_ssao.destroy();
     m_dynamicEntityRenderer.destroy();
     m_skybox.destroy();
     m_dynamicTerrain.destroy();
     window.close();
}
