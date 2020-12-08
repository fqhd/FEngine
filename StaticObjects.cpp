#include "StaticObjects.hpp"

void StaticObjects::init(Settings& settings){
     m_shader.init();
     m_renderer.init();

     m_renderer.begin();

     //Adding different models to batch renderer
     addSurface(settings, StaticColor(255, 200, 100));

     m_renderer.end();

}

void StaticObjects::render(Camera3D& camera){
     m_shader.bind();
     m_shader.loadViewMatrix(camera.getViewMatrix());
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadModelMatrix(glm::mat4(1.0f));
     m_renderer.render(m_shader);
     m_shader.unbind();
}

void StaticObjects::destroy(){
     m_shader.destroy();
     m_renderer.destroy();
}

void StaticObjects::addSurface(Settings& settings, StaticColor color){
     std::vector<Vertex> vertices;

     float offset = settings.worldWidth;

     vertices.push_back(Vertex(glm::vec3(-offset, -1, -offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(-offset, 1, -offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, 1, -offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, -1, -offset), glm::vec3(0, 0, 0)));

     vertices.push_back(Vertex(glm::vec3(-offset, -1, offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(-offset, 1, offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, 1, offset), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, -1, offset), glm::vec3(0, 0, 0)));

     unsigned int indices[] = { 0, 1, 2, 0, 2, 3, 4, 5, 1, 4, 1, 0, 4, 6, 5, 4, 7, 6, 1, 5, 6, 1, 6, 2, 0, 7, 4, 0, 3, 7, 3, 2, 6, 3, 6, 7  };

     m_renderer.addModel(vertices.data(), vertices.size(), indices, sizeof(indices)  / sizeof(indices[0]), color);
}
