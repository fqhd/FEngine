#include "MasterRenderer.hpp"

void MasterRenderer::init(unsigned int width, unsigned int height){
     createKernelSamples();
     createSSAONoiseTexture(width, height);

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

void MasterRenderer::renderScene(std::vector<Entity>& entities, Camera3D& camera, CubeTexture* texture){

     //Populating the G-Buffer
     m_gbuffer.bind();
     m_gbuffer.clear();
     renderObjectsInstanced(entities, camera);
     if (skyboxEnabled) renderSkybox(camera, texture);
     m_gbuffer.unbind();





     ////////////////////////////////////////////////////////////////////////////
     //////////////////////// THE REST OF THE FUNCTION IS SSAO CODE /////////////
     ////////////////////////////////////////////////////////////////////////////
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

void MasterRenderer::renderObjectsInstanced(std::vector<Entity>& entities, Camera3D& camera){

     if(entities.empty()){
          return;
     }

     std::stable_sort(entities.begin(), entities.end(), compare);

     std::vector<glm::mat4> matrices; // Matrices for each mesh that will be rendered
     std::vector<BatchedMesh> meshes; // Batched mesh containing the model information as well as the offsent for the matrices vector and number of instances of that entity drawn to the screen

     matrices.push_back(entities[0].transform.getMatrix()); // We push back the first matrix because we need to loop through the rest and compare the second with this first one
     meshes.emplace_back(entities[0].model, entities[0].texture, 0, 1); // We add the model with the offset 0 and a count of 1

     //Looping through entities and creating list of batched meshes for optimized rendering
     for(unsigned int i = 1; i < entities.size(); i++){
          if(entities[i].model->getVaoID() != entities[i - 1].model->getVaoID()){
               meshes.emplace_back(entities[i].model, entities[i].texture, matrices.size(), 0);
          }
          meshes.back().count++;
          matrices.push_back(entities[i].transform.getMatrix());
     }

     //Binding the shader and loading information (preparing for rendering)
     m_gbufferShader.bind();

     m_gbufferShader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_gbufferShader.loadViewMatrix(camera.getViewMatrix());

     for(auto& i : meshes){

          //Sending matrix data of all instanced models to gpu matrices buffer
          glBindBuffer(GL_ARRAY_BUFFER, i.model->getIboID());
          glBufferData(GL_ARRAY_BUFFER, i.count * sizeof(glm::mat4), &matrices[i.offset], GL_STREAM_DRAW);
          glBindBuffer(GL_ARRAY_BUFFER, 0);

          //Rendering instanced models
          glBindVertexArray(i.model->getVaoID());

          //Binding proper texture
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, i.texture->getID());

          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i.model->getEboID());
          glDrawElementsInstanced(GL_TRIANGLES, i.model->getNumVertices(), GL_UNSIGNED_INT, 0, i.count);
          glBindBuffer(GL_ARRAY_BUFFER, 0);

          //Unbinding texture
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, i.texture->getID());

          glBindVertexArray(0);

     }

     m_gbufferShader.unbind();

}


void MasterRenderer::renderSkybox(Camera3D& camera, CubeTexture* texture){
     m_cubemapShader.bind();
     m_cubemapShader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_cubemapShader.loadViewMatrix(glm::mat4(glm::mat3(camera.getViewMatrix())));

     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getID());
     glDepthMask(GL_FALSE);
     glDepthFunc(GL_LEQUAL);

     m_cube.render();

     glDepthFunc(GL_LESS);
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
     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, 0);
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, 0);
     glActiveTexture(GL_TEXTURE0);
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

bool MasterRenderer::compare(Entity a, Entity b){
     return (a.texture->getID() < b.texture->getID());
}
