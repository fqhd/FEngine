#include "SSAOBlurShader.hpp"

void SSAOBlurShader::init(){
     loadShader("res/shaders/ssao_vertex_shader.glsl", "res/shaders/blur_fragment_shader.glsl");
     bind();
     loadUniforms();
     unbind();
}

void SSAOBlurShader::loadUniforms(){
     glUniform1i(glGetUniformLocation(m_programID, "ssaoTexture"), 0);
}
