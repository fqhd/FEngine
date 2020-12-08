#ifndef CUBEMAP_SHADER_H
#define CUBEMAP_SHADER_H

#include "Shader.hpp"
#include <glm/glm.hpp>

class CubemapShader : public Shader {
public:

     void init();
     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);

private:

     void getUniformLocations();

     //Locations
     GLint m_viewMatrixLocation = 0;
     GLint m_projectionMatrixLocation = 0;



};

#endif
