#include "CubemapShader.hpp"

void CubemapShader::init(){
     loadShader("res/shaders/cubemap_vertex_shader.glsl", "res/shaders/cubemap_fragment_shader.glsl");
     bind();
     getUniformLocations();
     unbind();
}

void CubemapShader::getUniformLocations(){
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
}

void CubemapShader::loadProjectionMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void CubemapShader::loadViewMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}
