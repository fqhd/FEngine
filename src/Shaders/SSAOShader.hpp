#ifndef SSAO_SHADER_H
#define SSAO_SHADER_H

#include "Shader.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>


class SSAOShader : public Shader {
public:

     void init(std::vector<glm::vec3>& samples, unsigned int width, unsigned int height);

     void loadProjectionMatrix(const glm::mat4& matrix);

private:

     void loadUniforms();
     void loadNoiseScale(const glm::vec2& noise);
     void getUniformLocations();
     void loadKernelSamples(std::vector<glm::vec3>& samples);


     //Uniform Locations
     GLint m_projectionMatrixLocation = 0;
     GLint m_noiseLocation = 0;

};

#endif
