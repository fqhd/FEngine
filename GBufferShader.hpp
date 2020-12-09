#ifndef GBUFFER_SHADER_H
#define GBUFFER_SHADER_H

#include "Shader.hpp"


class GBufferShader : public Shader {
public:

     void init();
     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);
     void loadModelMatrix(const glm::mat4& matrix);
     void loadColor(StaticColor color);

private:

     void getUniformLocations();

     //Uniform Locations
     GLint m_viewMatrixLocation = 0;



};
#endif
