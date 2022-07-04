#include "SSAOLightingShader.hpp"

void SSAOLightingShader::init(unsigned int width, unsigned int height){
     loadShader("res/shaders/ssao_vertex_shader.glsl", "res/shaders/ssao_lighting_fragment_shader.glsl");
     bind();
     loadUniforms();
     getUniformLocations();
     loadInverseTextureSize(glm::vec2(1.0f/width, 1.0f/height));
     unbind();
}

void SSAOLightingShader::loadUniforms(){
     glUniform1i(glGetUniformLocation(m_programID, "positionTexture"), 0);
     glUniform1i(glGetUniformLocation(m_programID, "normalTexture"), 1);
     glUniform1i(glGetUniformLocation(m_programID, "albedoTexture"), 2);
     glUniform1i(glGetUniformLocation(m_programID, "ssaoTexture"), 3);
}

void SSAOLightingShader::getUniformLocations(){
     m_inverseTextureSizeLocation = glGetUniformLocation(m_programID, "inverseTextureSize");
}

void SSAOLightingShader::loadInverseTextureSize(const glm::vec2& inverse){
     glUniform2fv(m_inverseTextureSizeLocation, 1, &inverse[0]);
}
