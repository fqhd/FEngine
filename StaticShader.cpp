#include "StaticShader.hpp"

void StaticShader::init(){
     loadShader("res/shaders/static_vertex_shader.glsl", "res/shaders/static_fragment_shader.glsl");
     bind();
     getUniformLocations();
     unbind();
}

void StaticShader::getUniformLocations(){
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
}

void StaticShader::loadProjectionMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void StaticShader::loadViewMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}
