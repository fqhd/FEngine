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
     movePlayer(manager);

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
                    m_entities.emplace_back(Transform(glm::vec3(x + 0.5f, 1.5f, z+0.5f), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), m_engine.assets.getPlayerModel(), StaticColor(200, 20, 240));
               }
          }
     }

     m_engine.camera.center = glm::vec3(settings.worldWidth / 2, 0.0f, settings.worldWidth / 2);

     m_engine.masterRenderer.batchRenderer.begin();

     createSurface(settings);

     m_engine.masterRenderer.batchRenderer.end();

}

void Game::createSurface(Settings& settings){
     std::vector<Vertex> vertices;

     float offset = settings.worldWidth;

     vertices.push_back(Vertex(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, 1, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, 0, 0), glm::vec3(0, 0, 0)));

     vertices.push_back(Vertex(glm::vec3(0, 0, offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(0, 1, offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, 1, offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, 0, offset), glm::vec3(0, 0, 0)));

     unsigned int indices[] = { 0, 1, 2, 0, 2, 3, 4, 5, 1, 4, 1, 0, 4, 6, 5, 4, 7, 6, 1, 5, 6, 1, 6, 2, 0, 7, 4, 0, 3, 7, 3, 2, 6, 3, 6, 7  };

     m_engine.masterRenderer.batchRenderer.addModel(vertices.data(), vertices.size(), indices, sizeof(indices)  / sizeof(indices[0]), StaticColor(255, 255, 255));
}

void Game::movePlayer(InputManager& manager){

}
