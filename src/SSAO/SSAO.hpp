#ifndef SSAO_H
#define SSAO_H

#include <random>

#include "GBuffer.hpp"
#include "Quad.hpp"
#include "SSAOShader.hpp"
#include "SSAOBlurShader.hpp"
#include "SSAOLightingShader.hpp"
#include "SSAOBlurBuffer.hpp"
#include "SSAOBuffer.hpp"
#include "Camera.hpp"
#include "SSAOTexture.hpp"


class SSAO {
public:

     void init(unsigned int width, unsigned int height);
     void bind();
     void unbind();
     void render(Camera& camera);
     void destroy();

private:

     float lerp(float a, float b, float f);
     void renderSSAOQuad(Camera& camera);
     void renderBlurQuad();
     void createKernelSamples();
     void createSSAONoiseTexture(unsigned int width, unsigned int height);
     void renderSSAOLightingQuad();

     //OBjects
     GBuffer m_gBuffer;
     Quad m_quad;
     SSAOTexture m_noiseTexture;
     SSAOBuffer m_ssaoBuffer;
     SSAOBlurBuffer m_blurBuffer;

     //Shaders
     SSAOShader m_ssaoShader;
     SSAOBlurShader m_blurShader;
     SSAOLightingShader m_ssaoLightingShader;

     //Private variables
     std::vector<glm::vec3> m_kernelSamples;
     std::mt19937 m_generator;

};

#endif
