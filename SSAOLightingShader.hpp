#ifndef SSAO_LIGHTING_SHADER_H
#define SSAO_LIGHTING_SHADER_H

#include "Shader.hpp"
#include "Light.hpp"

class SSAOLightingShader : public Shader {
public:

     void init();

     loadLight(const Light& light);


private:

     void loadUniforms();
     void getUniformLocations();


     //Uniform Locations
     GLint m_lightColorLocation = 0;
     GLint m_lightPositionLocation = 0;
     GLint m_lightQuadraticLocation = 0;
};


#endif
