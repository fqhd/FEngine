#include "MasterRenderer.hpp"

void MasterRenderer::init(unsigned int width, unsigned int height){
     m_ssao.init(width, height);
     m_skybox.init("res/textures/sky/", "res/textures/sky/");
     m_dynamicEntityRenderer.init();
}

void MasterRenderer::renderScene(std::vector<Entity>& entities, Camera& camera){

     m_ssao.bind();

     m_dynamicEntityRenderer.render(entities, camera);
     m_skybox.render(camera);

     m_ssao.unbind();


     m_ssao.render(camera);

}

void MasterRenderer::destroy(){
     m_ssao.destroy();
     m_dynamicEntityRenderer.destroy();
     m_skybox.destroy();
}
