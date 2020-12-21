#include "SSAO.hpp"

void SSAO::init(unsigned int width, unsigned int height){
     createKernelSamples();
     createSSAONoiseTexture(width, height);

     m_gBuffer.init(width, height);
     m_quad.init();
     m_ssaoShader.init(m_kernelSamples, width, height);
     m_ssaoBuffer.init(width, height);
     m_blurBuffer.init(width, height);
     m_blurShader.init();
     m_ssaoLightingShader.init(width, height);
     m_generator.seed(500);

}

void SSAO::createSSAONoiseTexture(unsigned int width, unsigned int height) {
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

void SSAO::bind(){
     m_gBuffer.bind();
     m_gBuffer.clear();
}

void SSAO::unbind(){
     m_gBuffer.unbind();
}

void SSAO::render(Camera& camera){
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

void SSAO::renderSSAOQuad(Camera& camera){
     m_ssaoShader.bind();

     //Loading uniforms
     m_ssaoShader.loadProjectionMatrix(camera.getProjectionMatrix());

     //Binding textures to their appropriate IDs
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_gBuffer.getPositionTextureID());
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, m_gBuffer.getNormalTextureID());
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
     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, 0);
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, 0);
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, 0);

     m_ssaoShader.unbind();

}

void SSAO::renderSSAOLightingQuad(){
     m_ssaoLightingShader.bind();

     //Binding textures
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_gBuffer.getPositionTextureID());
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, m_gBuffer.getNormalTextureID());
     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, m_gBuffer.getAlbedoTextureID());
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

     glActiveTexture(GL_TEXTURE3);
     glBindTexture(GL_TEXTURE_2D, 0);
     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, 0);
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, 0);
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, 0);

     m_ssaoLightingShader.unbind();
}


void SSAO::renderBlurQuad(){
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


void SSAO::createKernelSamples(){
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


float SSAO::lerp(float a, float b, float f) {
    return a + f * (b - a);
}

void SSAO::destroy(){
     m_quad.destroy();
     m_gBuffer.destroy();
     m_ssaoShader.destroy();
     m_noiseTexture.destroy();
     m_ssaoBuffer.destroy();
     m_blurShader.destroy();
     m_ssaoLightingShader.destroy();

}
