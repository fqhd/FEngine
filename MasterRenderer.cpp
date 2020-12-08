#include "MasterRenderer.hpp"

void MasterRenderer::init(Settings& settings){
     m_batchRenderer.init();
     m_staticShader.init();

     addStaticObjects(settings);
}

void MasterRenderer::renderScene(std::vector<Entity>& entities, Camera3D& camera){

     //Rendering Entites
     m_staticShader.bind();
     m_staticShader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_staticShader.loadViewMatrix(camera.getViewMatrix());

     m_batchRenderer.render(m_staticShader);
     renderEntities(entities);


     m_staticShader.unbind();

}

void MasterRenderer::renderEntities(std::vector<Entity>& entities){
     for(auto& i : entities){
          m_staticShader.loadModelMatrix(i.transform.getMatrix());
          m_staticShader.loadColor(i.color);
          i.render();
     }
}

void MasterRenderer::destroy(){
     m_batchRenderer.destroy();
     m_staticShader.destroy();
}


void MasterRenderer::addStaticObjects(Settings& settings){
     m_batchRenderer.begin();
     addSurface(settings, StaticColor(255, 0, 0));
     m_batchRenderer.end();
}


//Static Object Functions
void MasterRenderer::addSurface(Settings& settings, StaticColor color){
     std::vector<Vertex> vertices;

     float offset = settings.worldWidth;

     vertices.push_back(Vertex(glm::vec3(-offset, -0.5f, -offset), glm::vec3(-1, -1, -1)));
     vertices.push_back(Vertex(glm::vec3(-offset, 0.5f, -offset), glm::vec3(-1, 1, -1)));
     vertices.push_back(Vertex(glm::vec3(offset, 0.5f, -offset), glm::vec3(1, 1, -1)));
     vertices.push_back(Vertex(glm::vec3(offset, -0.5f, -offset), glm::vec3(1, -1, -1)));

     vertices.push_back(Vertex(glm::vec3(-offset, -0.5f, offset), glm::vec3(-1, -1, 1)));
     vertices.push_back(Vertex(glm::vec3(-offset, 0.5f, offset), glm::vec3(-1, 1, 1)));
     vertices.push_back(Vertex(glm::vec3(offset, 0.5f, offset), glm::vec3(1, 1, 1)));
     vertices.push_back(Vertex(glm::vec3(offset, -0.5f, offset), glm::vec3(1, -1, 1)));

     unsigned int indices[] = { 0, 1, 2, 0, 2, 3, 4, 5, 1, 4, 1, 0, 4, 6, 5, 4, 7, 6, 1, 5, 6, 1, 6, 2, 0, 7, 4, 0, 3, 7, 3, 2, 6, 3, 6, 7  };

     m_batchRenderer.addModel(vertices.data(), vertices.size(), indices, sizeof(indices)  / sizeof(indices[0]), color);
}
