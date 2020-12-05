#include "EntityRenderer.hpp"

void EntityRenderer::init(){
     m_shader.loadShader("res/shaders/model_vertex_shader.glsl", "res/shaders/model_fragment_shader.glsl");
     m_shader.bind();
     m_shader.getUniformLocations();
     m_shader.unbind();
}

void EntityRenderer::renderEntities(Camera3D& camera){

     m_shader.bind();
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());
     for(auto& i : entities){
          m_shader.loadModelMatrix(i.transform.getMatrix());
          i.render();
     }
     m_shader.unbind();

}


void EntityRenderer::destroy(){
     m_shader.destroy();
}
