#include "TerrainShader.hpp"

void TerrainShader::init(){
     loadShader("res/shaders/terrain_vertex_shader.glsl", "res/shaders/terrain_fragment_shader.glsl");
     bind();
     loadUniforms();
     getUniformLocations();
     unbind();
}

void TerrainShader::loadProjectionMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void TerrainShader::loadViewMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void TerrainShader::loadUniforms(){
     glUniform1i(glGetUniformLocation(m_programID, "ourTexture"), 0);
}

void TerrainShader::loadModelMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void TerrainShader::getUniformLocations(){
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
     m_modelMatrixLocation = glGetUniformLocation(m_programID, "model");
}
