#include "SSAOShader.hpp"

void SSAOShader::init(std::vector<glm::vec3>& samples, unsigned int width, unsigned int height){
     loadShader("res/shaders/ssao_vertex_shader.glsl", "res/shaders/ssao_fragment_shader.glsl");
     bind();
     loadUniforms();
     getUniformLocations();
     loadKernelSamples(samples);
     loadNoiseScale(glm::vec2(width/4.0f, height/4.0f));
     unbind();
}

void SSAOShader::loadUniforms(){
     glUniform1i(glGetUniformLocation(m_programID, "positionTexture"), 0);
     glUniform1i(glGetUniformLocation(m_programID, "normalTexture"), 1);
     glUniform1i(glGetUniformLocation(m_programID, "noiseTexture"), 2);
}

void SSAOShader::loadKernelSamples(std::vector<glm::vec3>& samples){
     for(unsigned int i = 0; i < samples.size(); i++){
          glUniform3fv(glGetUniformLocation(m_programID, std::string("samples[" + std::to_string(i) + "]").c_str()), 1, &samples[i][0]);
     }
}

void SSAOShader::getUniformLocations(){
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_noiseLocation = glGetUniformLocation(m_programID, "noise");
}

void SSAOShader::loadProjectionMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void SSAOShader::loadNoiseScale(const glm::vec2& noise){
     glUniform2fv(m_noiseLocation, 1, &noise[0]);
}
