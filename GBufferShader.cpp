#include "GBufferShader.hpp"

void GBufferShader::init(){
     loadShader("res/shaders/gbuffer_vertex_shader.glsl", "res/shaders/gbuffer_fragment_shader.glsl");
     bind();
     getUniformLocations();
     unbind();
}

void GBufferShader::getUniformLocations(){
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
     m_modelMatrixLocation = glGetUniformLocation(m_programID, "model");
     m_colorLocation = glGetUniformLocation(m_programID, "color");
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

void GBufferShader::loadColor(StaticColor color){
     glm::vec3 c;

     c.x = color.r/255.0f;
     c.y = color.g/255.0f;
     c.z = color.b/255.0f;

     glUniform3fv(m_colorLocation, 1, &c[0]);

}
