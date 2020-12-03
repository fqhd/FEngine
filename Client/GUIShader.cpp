#include "GUIShader.hpp"

void GUIShader::getUniformLocations(){
     bind();
     m_matrixLocation = glGetUniformLocation(m_programID, "matrix");
     unbind();
}

void GUIShader::loadMatrix(const glm::mat4& matrix){
     glUniformMatrix4fv(m_matrixLocation, 1, GL_FALSE, &matrix[0][O]);
}
