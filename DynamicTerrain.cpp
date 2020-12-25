#include "DynamicTerrain.hpp"


void DynamicTerrain::init(unsigned int resolution){
     m_vertices = new Vertex[resolution * resolution];
     m_shader.init();
     m_terrain.init();
     m_indexBuffer = Utils::createIndicesBuffer(resolution, resolution);
     m_resolution = resolution;
}

void DynamicTerrain::update(Camera& camera){
     updateTerrainBasedOnPosition(glm::vec2(camera.getPosition().x, camera.getPosition().z));
}

void DynamicTerrain::updateTerrainBasedOnPosition(const glm::vec2& position){

     std::vector<Vertex> vertices;

     for(unsigned int z = 0; z < m_resolution; z++){
          for(unsigned int x = 0; x < m_resolution; x++){

               float height = glm::perlin(glm::vec2((x + position.x) / (float) m_resolution * 4, (z + position.y) / (float) m_resolution * 4));

               vertices.emplace_back(glm::vec3((x + position.x) - m_resolution / 2, height * 8.0f, (z + position.y) - m_resolution/2), glm::vec3(0, 1, 0), glm::vec2(0, 0));
          }
     }

     m_terrain.uploadData(vertices.data(), vertices.size());

}

void DynamicTerrain::render(Camera& camera){
     m_shader.bind();

     //Send camera uniforms to shader
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());

     //glActiveTexture(GL_TEXTURE0);
     //glBindTexture(GL_TEXTURE_2D, m_texture->getID());

     //Rendering
     m_terrain.render(m_indexBuffer);


     m_shader.unbind();
}



void DynamicTerrain::destroy(){
     m_shader.destroy();
     m_indexBuffer.destroy();

}
