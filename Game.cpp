#include "Game.hpp"

#include <iostream>

void Game::init(Settings& settings){

     m_entityHandler.init();
     m_camera.init(settings.screenWidth, settings.screenHeight);
     m_surface.init(settings);
     m_batchRenderer.init();
     m_shader.init();

     m_batchRenderer.begin();
     std::vector<Vertex> vertices;

     vertices.push_back(Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(0, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(1, -1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 0)));

     unsigned int indices[] = {0, 1, 2};

     m_batchRenderer.addModel(vertices.data(), vertices.size(), indices, sizeof(indices)  / sizeof(indices[0]), 0);


     m_batchRenderer.end();

}

void Game::update(){

}

void Game::render(){

     m_entityHandler.renderEntities(m_camera);

     m_shader.bind();
     m_shader.loadViewMatrix(m_camera.getViewMatrix());
     m_shader.loadProjectionMatrix(m_camera.getProjectionMatrix());
     m_batchRenderer.render();
     m_shader.unbind();

}

void Game::destroy(){
     m_shader.destroy();
     m_surface.destroy();
     m_entityHandler.destroy();
     m_batchRenderer.destroy();
}
