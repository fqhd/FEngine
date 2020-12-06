#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#include "Shader.hpp"
#include "Vertex.hpp"
#include <glm/glm.hpp>

class StaticShader : public Shader {
public:

     void init();

     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);
     void loadColor(StaticColor color);

private:

     void getUniformLocations();

     GLint m_projectionMatrixLocation = 0;
     GLint m_viewMatrixLocation = 0;
     GLint m_colorLocation = 0;


};

#endif
