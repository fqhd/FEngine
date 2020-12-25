#ifndef DYNAMIC_TERRAIN_SHADER_H
#define DYNAMIC_TERRAIN_SHADER_H

#include "Shader.hpp"


class DynamicTerrainShader : public Shader {
public:

     void init();
     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);
     void loadModelMatrix(const glm::mat4& matrix);

private:

     void loadUniforms();
     void getUniformLocations();

     //Uniform Locations
     GLint m_projectionMatrixLocation = 0;
     GLint m_viewMatrixLocation = 0;
     GLint m_modelMatrixLocation = 0;

};

#endif
