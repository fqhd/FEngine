#include "Game.hpp"

#include <iostream>

void Game::init(Settings& settings){

     m_assets.init();
     m_entityHandler.init();
     m_camera.init(settings.screenWidth, settings.screenHeight);

     m_staticObjects.init(settings);


}

void Game::update(InputManager& manager, Settings& settings){
     m_camera.move(manager, settings);

}

void Game::render(){

     m_entityHandler.renderEntities(m_camera);
     m_staticObjects.render(m_camera);

}

void Game::destroy(){
     m_entityHandler.destroy();
     m_staticObjects.destroy();
}
