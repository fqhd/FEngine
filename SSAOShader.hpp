#ifndef SSAO_SHADER_H
#define SSAO_SHADER_H

#include "Shader.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>


class SSAOShader : public Shader {
public:

     void init(std::vector<glm::vec3>& samples);

     void loadProjectionMatrix(const glm::mat4& matrix);

private:

     void loadUniforms();
     void getUniformLocations();
     void loadKernelSamples(std::vector<glm::vec3>& samples);


     //Uniform Locations
     GLint m_projectionMatrixLocation = 0;

};

#endif
