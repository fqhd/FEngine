#include "StaticTerrainShader.hpp"

void StaticTerrainShader::init(){
     loadShader("res/shaders/static_terrain_vertex_shader.glsl", "res/shaders/static_terrain_fragment_shader.glsl");
     bind();
     loadUniforms();
     getUniformLocations();
     unbind();
}

void StaticTerrainShader::loadProjectionMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void StaticTerrainShader::loadViewMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void StaticTerrainShader::loadUniforms(){
     glUniform1i(glGetUniformLocation(m_programID, "ourTexture"), 0);
}
void StaticTerrainShader::getUniformLocations(){
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
}
