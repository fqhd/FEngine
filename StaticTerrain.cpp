#include "StaticTerrain.hpp"

void StaticTerrain::loadFromFile(){

     //Creating data
     std::vector<Vertex> vertices;
     vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(0, -1, 0), glm::vec2(0, 0));
     vertices.emplace_back(glm::vec3(10, 0, 0), glm::vec3(0, -1, 0), glm::vec2(0, 0));
     vertices.emplace_back(glm::vec3(10, 0, 10), glm::vec3(0, -1, 0), glm::vec2(0, 0));

     //Creating indices
     std::vector<unsigned int> indices;
     indices.push_back(0);
     indices.push_back(1);
     indices.push_back(2);

     m_terrain.init();
     m_terrain.uploadData(vertices, indices);
     m_shader.init();


}

void StaticTerrain::render(Camera& camera){
     m_shader.bind();

     //Send camera uniforms to shader
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());

     //Rendering
     m_terrain.render();


     m_shader.unbind();
}

void StaticTerrain::destroy(){
     m_shader.destroy();
     m_terrain.destroy();
}
