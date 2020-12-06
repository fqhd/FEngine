#include "StaticObjects.hpp"

void StaticObjects::init(){
     m_shader.init();
     m_renderer.init();

     m_renderer.begin();

     //Adding different models to batch renderer
     addSurface();

     m_renderer.end();

}

void StaticObjects::render(Camera3D& camera){
     m_shader.bind();
     m_shader.loadViewMatrix(camera.getViewMatrix());
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_renderer.render();
     m_shader.unbind();
}

void StaticObjects::destroy(){
     m_shader.destroy();
     m_renderer.destroy();
}

void StaticObjects::addSurface(){
     std::vector<Vertex> vertices;

     vertices.push_back(Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(0, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(1, -1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 0)));

     unsigned int indices[] = { 0, 1, 2 };

     m_renderer.addModel(vertices.data(), vertices.size(), indices, sizeof(indices)  / sizeof(indices[0]), 0);
}
