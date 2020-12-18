#include "MasterRenderer.hpp"

void MasterRenderer::init(unsigned int width, unsigned int height){
     createKernelSamples();
     createSSAONoiseTexture(width, height);

     m_batchRenderer.init();
     m_gbuffer.init(width, height);
     m_gbufferShader.init();
     m_cube.init();
     m_cubemapShader.init();
     m_quad.init();
     m_ssaoShader.init(m_kernelSamples, width, height);
     m_ssaoBuffer.init(width, height);
     m_blurBuffer.init(width, height);
     m_blurShader.init();
     m_ssaoLightingShader.init(width, height);
     m_generator.seed(500);

     m_guiRenderer.init();
     m_guiShader.init();

}

void MasterRenderer::renderScene(std::vector<Entity>& entities, Camera3D& camera, Assets& assets){

     //Populating the G-Buffer
     m_gbuffer.bind();
     m_gbuffer.clear();
     renderSkybox(camera, assets);
     renderObjects(entities, camera);
     m_gbuffer.unbind();

     //Rendering the SSAO Texture
     m_ssaoBuffer.bind();
     m_ssaoBuffer.clear();
     renderSSAOQuad(camera);
     m_ssaoBuffer.unbind();

     //Rendering the SSAO Blurred Texture
     m_blurBuffer.bind();
     m_blurBuffer.clear();
     renderBlurQuad();
     m_blurBuffer.unbind();


     //Rendering final SSAO lighting pass
     renderSSAOLightingQuad();


}

void MasterRenderer::renderObjects(std::vector<Entity>& entities, Camera3D& camera){
     m_gbufferShader.bind();

     m_gbufferShader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_gbufferShader.loadViewMatrix(camera.getViewMatrix());

     m_batchRenderer.render(m_gbufferShader);

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

     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_CUBE_MAP, assets.getSkyTexture()->getID());
     glDepthMask(GL_FALSE);

     m_cube.render();

     glDepthMask(GL_TRUE);
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

     m_cubemapShader.unbind();
}

void MasterRenderer::renderBlurQuad(){
     m_blurShader.bind();

     //Binding texture
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_ssaoBuffer.getTextureID());

     //Disabling GL States
     glDisable(GL_DEPTH_TEST);
     glDisable(GL_CULL_FACE);
     glDisable(GL_BLEND);

     m_quad.render();

     //Restoring GL States
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glEnable(GL_BLEND);

     //Unbinding texture
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, 0);

     m_blurShader.unbind();
}

void MasterRenderer::renderSSAOQuad(Camera3D& camera){
     m_ssaoShader.bind();

     //Loading uniforms
     m_ssaoShader.loadProjectionMatrix(camera.getProjectionMatrix());

     //Binding textures to their appropriate IDs
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_gbuffer.getPositionTextureID());
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, m_gbuffer.getNormalTextureID());
     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, m_noiseTexture.getID());

     //Enabling GL States
     glDisable(GL_DEPTH_TEST);
     glDisable(GL_CULL_FACE);
     glDisable(GL_BLEND);

     m_quad.render();

     //Restoring GL States
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

void MasterRenderer::renderSSAOLightingQuad(){
     m_ssaoLightingShader.bind();

     //Binding textures
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_gbuffer.getPositionTextureID());
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, m_gbuffer.getNormalTextureID());
     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, m_gbuffer.getAlbedoTextureID());
     glActiveTexture(GL_TEXTURE3);
     glBindTexture(GL_TEXTURE_2D, m_blurBuffer.getTextureID());

     //Disabling GL States
     glDisable(GL_DEPTH_TEST);
     glDisable(GL_CULL_FACE);
     glDisable(GL_BLEND);

     m_quad.render();

     //Restoring GL States
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
     glActiveTexture(GL_TEXTURE3);
     glBindTexture(GL_TEXTURE_2D, 0);

     m_ssaoLightingShader.unbind();
}

void MasterRenderer::renderEntities(std::vector<Entity>& entities){
     for(auto& i : entities){
          m_gbufferShader.loadModelMatrix(i.transform.getMatrix());
          m_gbufferShader.loadColor(i.color);
          i.render();
     }
}

void MasterRenderer::createKernelSamples(){
     std::uniform_real_distribution<float> randomFloats(0.0, 1.0);

     for (unsigned int i = 0; i < 64; ++i) {
          glm::vec3 sample(
               randomFloats(m_generator) * 2.0 - 1.0,
               randomFloats(m_generator) * 2.0 - 1.0,
               randomFloats(m_generator)
          );
          sample  = glm::normalize(sample);
          sample *= randomFloats(m_generator);

          //Pushing them closer to the center
          float scale = (float)i / 64.0;
          scale = lerp(0.1f, 1.0f, scale * scale);
          sample *= scale;

          //Adding the sample to the vector of samples
          m_kernelSamples.push_back(sample);
     }

}

void MasterRenderer::createSSAONoiseTexture(unsigned int width, unsigned int height) {
     std::uniform_real_distribution<float> randomFloats(0.0, 1.0);

     std::vector<glm::vec3> ssaoNoise;
     for (unsigned int i = 0; i < 16; i++) {
          glm::vec3 noise(
               randomFloats(m_generator) * 2.0 - 1.0,
               randomFloats(m_generator) * 2.0 - 1.0,
               0.0f
          );

          ssaoNoise.push_back(noise);
     }

     m_noiseTexture.init(width, height, ssaoNoise);

}

float MasterRenderer::lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

void MasterRenderer::renderGUI(GUI& gui, Camera2D& camera){

     m_guiRenderer.begin();
     for(auto& i : gui.buttons) i.render(m_guiRenderer);
     for(auto& i : gui.images) i.render(m_guiRenderer);
     m_guiRenderer.end();


     m_guiShader.bind();
     m_guiShader.loadMatrix(camera.getMatrix());

     m_guiRenderer.render();

     m_guiShader.unbind();

}

void MasterRenderer::destroy(){
     m_batchRenderer.destroy();
     m_quad.destroy();
     m_cube.destroy();
     m_gbufferShader.destroy();
     m_gbuffer.destroy();
     m_ssaoShader.destroy();
     m_cubemapShader.destroy();
     m_noiseTexture.destroy();
     m_ssaoBuffer.destroy();
     m_blurShader.destroy();
     m_ssaoLightingShader.destroy();
     m_guiRenderer.destroy();
     m_guiShader.destroy();
}
