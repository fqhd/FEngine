     #include "Game.hpp"


void Game::init(Settings& settings){

     //Engine Inits
     m_assets.init();
     m_camera.init(settings.screenWidth, settings.screenHeight);
     m_cubemap.init();
     m_masterRenderer.init(settings);

     //Game Inits
     addEntities();


}

void Game::update(InputManager& manager, Settings& settings){
     m_camera.move(manager, settings);
     m_cubemap.update();
}

void Game::render(){

     m_cubemap.render(m_camera, m_assets);

     m_masterRenderer.renderScene(m_entityHandler.entities, m_camera);


}

void Game::destroy(){
     m_cubemap.destroy();
     m_masterRenderer.destroy();
}

void Game::addEntities(){
     m_entityHandler.entities.emplace_back(Transform(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), m_assets.getPlayerModel(), StaticColor(200, 20, 240));
}
