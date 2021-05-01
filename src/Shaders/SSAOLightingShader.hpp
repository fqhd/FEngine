#ifndef SSAO_LIGHTING_SHADER_H
#define SSAO_LIGHTING_SHADER_H


#include "../Utils/Shader.hpp"


class SSAOLightingShader : public Shader {
public:

     void init(unsigned int width, unsigned int height);


private:

     void loadUniforms();
     void loadInverseTextureSize(const glm::vec2& inverse);
     void getUniformLocations();

     //Uniform Locations
     GLint m_inverseTextureSizeLocation;


};


#endif
