#include "MasterRenderer.hpp"

void MasterRenderer::init(Settings& settings){
     batchRenderer.init();
     m_staticShader.init();
}

void MasterRenderer::renderScene(std::vector<Entity>& entities, Camera3D& camera){

     //Rendering Entites
     m_staticShader.bind();

     m_staticShader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_staticShader.loadViewMatrix(camera.getViewMatrix());

     batchRenderer.render(m_staticShader);
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
     batchRenderer.destroy();
     m_staticShader.destroy();
}
