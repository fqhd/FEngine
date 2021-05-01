#ifndef SSAO_BLUR_SHADER_H
#define SSAO_BLUR_SHADER_H

#include "../Utils/Shader.hpp"


class SSAOBlurShader : public Shader {
public:

     void init();


private:

     void loadUniforms();

};

#endif
