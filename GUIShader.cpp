#include "GUIShader.hpp"

void GUIShader::init(){
     loadShader("res/shaders/gui_vertex_shader.glsl", "res/shaders/gui_fragment_shader.glsl");
     bind();
     getUniformLocations();
     unbind();
}

void GUIShader::getUniformLocations(){
     m_matrixLocation = glGetUniformLocation(m_programID, "matrix");
}

void GUIShader::loadMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_matrixLocation, 1, GL_FALSE, &matrix[0][0]);
}
