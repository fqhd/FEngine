#include "Game.hpp"

#include <fstream>

void Game::init(Settings& settings){

     //Engine Inits
     m_engine.init(settings);
     loadLevel(settings);


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
     m_world.destroy();
     m_engine.destroy();
}

void Game::loadLevel(Settings& settings){
     m_world.loadWorld(settings);

     //Add player entity where player is supposed to be
     for(unsigned int z = 0; z < settings.worldWidth; z++){
          for(unsigned int x = 0; x < settings.worldWidth; x++){
               if(m_world.getTile(x, z, settings.worldWidth) == 'P'){
                    m_entities.emplace_back(Transform(glm::vec3(x, 1, z), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), m_engine.assets.getPlayerModel(), StaticColor(200, 20, 240));
               }
          }
     }


}
