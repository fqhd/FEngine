#pragma once
#include <glm/glm.hpp>

#include "../Utils/Shader.hpp"

class GUIShader : public Shader {
public:

     void init();
     void getUniformLocations();
     void loadMatrix(const glm::mat4& matrix);

private:

     GLint m_matrixLocation = 0;

};
