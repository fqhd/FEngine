#include "EntityHandler.hpp"

void EntityHandler::init(){
     m_shader.init();
}

void EntityHandler::renderEntities(Camera3D& camera){

     m_shader.bind();
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());
     for(auto& i : entities){
          m_shader.loadModelMatrix(i.transform.getMatrix());
          i.render();
     }
     m_shader.unbind();

}

void EntityHandler::destroy(){
     m_shader.destroy();
}
