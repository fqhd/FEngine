#include "Game.hpp"


void Game::init(Settings& settings){

     m_assets.init();
     m_camera.init(settings.screenWidth, settings.screenHeight);
     m_staticObjects.init(settings);
     m_entityHandler.init(m_assets);
     m_cubemap.init();


}

void Game::update(InputManager& manager, Settings& settings){
     m_camera.move(manager, settings);
     m_cubemap.update();
}

void Game::render(){

     m_cubemap.render(m_camera, m_assets);

     m_entityHandler.renderEntities(m_camera);

     m_staticObjects.render(m_camera);


}

void Game::destroy(){
     m_cubemap.destroy();
     m_entityHandler.destroy();
     m_staticObjects.destroy();
}
