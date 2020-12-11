#include "SSAOLightingShader.hpp"

void SSAOLightingShader::init(){
     loadShader("res/shaders/ssao_vertex_shader.glsl", "res/shaders/ssao_lighting_fragment_shader.glsl");
     bind();
     loadUniforms();
     unbind();
}

void SSAOLightingShader::loadUniforms(){
     glUniform1i(glGetUniformLocation(m_programID, "positionTexture"), 0);
     glUniform1i(glGetUniformLocation(m_programID, "normalTexture"), 1);
     glUniform1i(glGetUniformLocation(m_programID, "albedoTexture"), 2);
     glUniform1i(glGetUniformLocation(m_programID, "ssaoTexture"), 3);
}
