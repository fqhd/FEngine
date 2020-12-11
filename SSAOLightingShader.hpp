#ifndef SSAO_LIGHTING_SHADER_H
#define SSAO_LIGHTING_SHADER_H

#include "Shader.hpp"

class SSAOLightingShader : public Shader {
public:

     void init();

private:

     void loadUniforms();

};


#endif
