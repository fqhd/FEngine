#include "MasterRenderer.hpp"

void MasterRenderer::init(Settings& settings){
     batchRenderer.init();
     m_gbuffer.init(settings.screenWidth, settings.screenHeight);
     m_gbufferShader.init();
     m_cube.init();
     m_cubemapShader.init();
     m_quad.init();
     m_ssaoShader.init();
}

void MasterRenderer::renderScene(std::vector<Entity>& entities, Camera3D& camera, Assets& assets){

     m_gbuffer.bind();
     m_gbuffer.clear();
     renderSkybox(camera, assets);
     renderObjects(entities, camera);
     m_gbuffer.unbind();

     renderSSAOQuad();


}

void MasterRenderer::renderObjects(std::vector<Entity>& entities, Camera3D& camera){
     m_gbufferShader.bind();

     m_gbufferShader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_gbufferShader.loadViewMatrix(camera.getViewMatrix());

     batchRenderer.render(m_gbufferShader);

     for(auto& i : entities){
          m_gbufferShader.loadModelMatrix(i.transform.getMatrix());
          m_gbufferShader.loadColor(i.color);
          i.render();
     }
     m_gbufferShader.unbind();
}

void MasterRenderer::renderSkybox(Camera3D& camera, Assets& assets){
     m_cubemapShader.bind();
     m_cubemapShader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_cubemapShader.loadViewMatrix(glm::mat4(glm::mat3(camera.getViewMatrix())));

     glBindTexture(GL_TEXTURE_CUBE_MAP, assets.getSkyTexture()->getID());
     glDepthFunc(GL_LEQUAL);

     m_cube.render();

     glDepthFunc(GL_LESS);
     glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

     m_cubemapShader.unbind();
}

void MasterRenderer::renderSSAOQuad(){
     m_ssaoShader.bind();

     //Binding textures to their appropriate IDs
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_gbuffer.getPositionTextureID());
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, m_gbuffer.getNormalTextureID());
     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, m_gbuffer.getAlbedoTextureID());

     glDisable(GL_DEPTH_TEST);
     glDisable(GL_CULL_FACE);
     glDisable(GL_BLEND);

     m_quad.render();

     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glEnable(GL_BLEND);

     //Unbinding all textures
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, 0);

     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, 0);

     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, 0);

     m_ssaoShader.unbind();

}

void MasterRenderer::renderEntities(std::vector<Entity>& entities){
     for(auto& i : entities){
          m_gbufferShader.loadModelMatrix(i.transform.getMatrix());
          m_gbufferShader.loadColor(i.color);
          i.render();
     }
}

void MasterRenderer::destroy(){
     batchRenderer.destroy();
     m_quad.destroy();
     m_cube.destroy();
     m_gbufferShader.destroy();
     m_gbuffer.destroy();
     m_ssaoShader.destroy();
     m_cubemapShader.destroy();
}
