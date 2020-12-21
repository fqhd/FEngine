#include "GBufferShader.hpp"

void GBufferShader::init(){
     loadShader("res/shaders/gbuffer_vertex_shader.glsl", "res/shaders/gbuffer_fragment_shader.glsl");
     bind();
     getUniformLocations();
     loadUniforms();
     unbind();
}

void GBufferShader::getUniformLocations(){
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
     m_modelMatrixLocation = glGetUniformLocation(m_programID, "model");
}

void GBufferShader::loadModelMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void GBufferShader::loadProjectionMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void GBufferShader::loadViewMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void GBufferShader::loadUniforms(){
     glUniform1i(glGetUniformLocation(m_programID, "ourTexture"), 0);
}
