#include "FXAA.hpp"

void FXAA::init(Window* window){
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glm::ivec2 size = window->getFramebufferSize();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Failed to create SSAO Blur Framebuffer with error: 0x" << Status << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    shader.init("res/shaders/fxaa");
    quad.init();
}

void FXAA::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FXAA::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FXAA::drawWithFXAA(){
    shader.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    quad.draw();
    shader.unbind();
}

void FXAA::destroy(){
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &textureID);
    quad.destroy();
}
