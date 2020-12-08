#include "EntityHandler.hpp"
#include "Transform.hpp"

void EntityHandler::init(Assets& assets){
     m_shader.init();

     entities.emplace_back(Transform(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), assets.getPlayerModel(), StaticColor(200, 175, 240));

}

void EntityHandler::renderEntities(Camera3D& camera){

     m_shader.bind();
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());


     for(auto& i : entities){
          m_shader.loadModelMatrix(i.transform.getMatrix());
          m_shader.loadColor(i.color);
          i.render();
     }
     m_shader.unbind();

}

void EntityHandler::destroy(){
     m_shader.destroy();
}
