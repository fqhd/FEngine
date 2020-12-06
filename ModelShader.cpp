#include "ModelShader.hpp"

void ModelShader::init(){
     loadShader("res/shaders/model_vertex_shader.glsl", "res/shaders/model_fragment_shader.glsl");
     bind();
     getUniformLocations();
     unbind();
}

void ModelShader::getUniformLocations(){
          m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
          m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
          m_modelMatrixLocation = glGetUniformLocation(m_programID, "model");
}

void ModelShader::loadProjectionMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ModelShader::loadViewMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ModelShader::loadModelMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}
