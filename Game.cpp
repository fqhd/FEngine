#include "Game.hpp"


void Game::init(Settings& settings){

     //Engine Inits
     m_engine.init(settings);
     loadLevel(settings.currentWorld);
     m_timer.start();

}

void Game::update(Settings& settings, GameStates& state){
     //Engine updates
     m_engine.update(settings);

     //Game updates
     movePlayer();

}

void Game::render(){

     m_engine.render(m_entities);

}

void Game::destroy(){
     m_world.destroy();
     m_engine.destroy();
}

void Game::loadLevel(unsigned int level){
     m_world.loadWorld(level);

     //Add player entity where player is supposed to be
     for(unsigned int z = 0; z < m_world.getWidth(); z++){
          for(unsigned int x = 0; x < m_world.getWidth(); x++){
               if(m_world.getTile(x, z, m_world.getWidth()) == 'P'){

                    m_entities.emplace_back(Transform(glm::vec3(x + 0.5f, 1.5f, z+0.5f), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), m_engine.assets.getPlayerModel(), StaticColor(200, 20, 240));

               }
          }
     }

     m_engine.camera3D.center = glm::vec3(m_world.getWidth() / 2, 0.5f, m_world.getWidth() / 2);

     m_engine.masterRenderer.batchRenderer.begin();

     createSurface();

     m_engine.masterRenderer.batchRenderer.end();

}

void Game::createSurface(){
     std::vector<Vertex> vertices;

     float offset = m_world.getWidth();

     vertices.push_back(Vertex(glm::vec3(0, 0, 0), glm::vec3(-1, -1, -1)));
     vertices.push_back(Vertex(glm::vec3(0, 1, 0), glm::vec3(-1, 1, -1)));
     vertices.push_back(Vertex(glm::vec3(offset, 1, 0), glm::vec3(1, 1, -1)));
     vertices.push_back(Vertex(glm::vec3(offset, 0, 0), glm::vec3(1, -1, -1)));

     vertices.push_back(Vertex(glm::vec3(0, 0, offset), glm::vec3(-1, -1, 1)));
     vertices.push_back(Vertex(glm::vec3(0, 1, offset), glm::vec3(-1, 1, 1)));
     vertices.push_back(Vertex(glm::vec3(offset, 1, offset), glm::vec3(1, 1, 1)));
     vertices.push_back(Vertex(glm::vec3(offset, 0, offset), glm::vec3(1, -1, 1)));

     unsigned int indices[] = { 0, 1, 2, 0, 2, 3, 4, 5, 1, 4, 1, 0, 4, 6, 5, 4, 7, 6, 1, 5, 6, 1, 6, 2, 0, 7, 4, 0, 3, 7, 3, 2, 6, 3, 6, 7  };

     m_engine.masterRenderer.batchRenderer.addModel(vertices.data(), vertices.size(), indices, sizeof(indices)  / sizeof(indices[0]), StaticColor(20, 100, 255));

}

void Game::movePlayer(){

     if(InputManager::isKeyDown(GLFW_KEY_LEFT)){
          m_entities[0].transform.move(glm::vec3(1, 0, 0) * 0.01f);
     }
     if(InputManager::isKeyDown(GLFW_KEY_UP)){
          m_entities[0].transform.move(glm::vec3(0, 0, 1) * 0.01f);
     }
     if(InputManager::isKeyDown(GLFW_KEY_RIGHT)){
          m_entities[0].transform.move(glm::vec3(-1, 0, 0) * 0.01f);
     }
     if(InputManager::isKeyDown(GLFW_KEY_DOWN)){
          m_entities[0].transform.move(glm::vec3(0, 0, -1) * 0.01f);
     }


}
