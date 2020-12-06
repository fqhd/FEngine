#ifndef MODELSHADER_H
#define MODELSHADER_H

#include "Shader.hpp"
#include <glm/glm.hpp>

class ModelShader : public Shader {
public:

     void init();


     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);
     void loadModelMatrix(const glm::mat4& matrix);



private:

     void getUniformLocations();

     GLint m_projectionMatrixLocation = 0;
     GLint m_viewMatrixLocation = 0;
     GLint m_modelMatrixLocation = 0;


};

#endif
