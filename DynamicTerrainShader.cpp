#include "DynamicTerrainShader.hpp"

void DynamicTerrainShader::init(){
     loadShader("res/shaders/dynamic_terrain_vertex_shader.glsl", "res/shaders/terrain_fragment_shader.glsl");
     bind();
     getUniformLocations();
     unbind();
}

void DynamicTerrainShader::loadProjectionMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void DynamicTerrainShader::loadViewMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void DynamicTerrainShader::loadModelMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void DynamicTerrainShader::getUniformLocations(){
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
     m_modelMatrixLocation = glGetUniformLocation(m_programID, "model");
}
