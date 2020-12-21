#ifndef STATIC_TERRAIN_SHADER_H
#define STATIC_TERRAIN_SHADER_H

#include "Shader.hpp"


class StaticTerrainShader : public Shader {
public:

     void init();
     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);


private:

     //Functions
     void loadUniforms();
     void getUniformLocations();

     //Uniform Locations
     GLuint m_projectionMatrixLocation = 0;
     GLuint m_viewMatrixLocation = 0;

};

#endif
