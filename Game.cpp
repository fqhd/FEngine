#include "Game.hpp"

#include <fstream>


void Game::init(Settings& settings){

     //Engine Inits
     m_engine.init(settings);


}

void Game::update(InputManager& manager, Settings& settings, GameStates& state){
     //Engine updates
     m_engine.update(manager, settings);

     //Game updates


}

void Game::render(){

     m_engine.render(m_entities);

}

void Game::destroy(){
     m_engine.destroy();
}

void Game::addEntities(){
     m_entities.emplace_back(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), m_engine.assets.getPlayerModel(), StaticColor(200, 20, 240));
}

void Game::loadLevel(unsigned int level){
     
}
