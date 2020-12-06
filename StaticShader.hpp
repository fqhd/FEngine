#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#include "Shader.hpp"

class StaticShader : public Shader {
public:

     void init();

     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);

private:

     void getUniformLocations();

     GLint m_projectionMatrixLocation = 0;
     GLint m_viewMatrixLocation = 0;


};
