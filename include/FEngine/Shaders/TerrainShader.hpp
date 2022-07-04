#ifndef TERRAIN_SHADER_H
#define TERRAIN_SHADER_H

#include "../Utils/Shader.hpp"


class TerrainShader : public Shader {
public:

     void init();
     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);
     void loadModelMatrix(const glm::mat4& matrix);


private:

     //Functions
     void loadUniforms();
     void getUniformLocations();

     //Uniform Locations
     GLint m_projectionMatrixLocation = 0;
     GLint m_viewMatrixLocation = 0;
     GLint m_modelMatrixLocation = 0;

};

#endif
