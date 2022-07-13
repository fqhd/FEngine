#include "GBuffer.hpp"
#include <iostream>

void GBuffer::init(unsigned int width, unsigned int height)
{
    glGenFramebuffers(1, &fboID);
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);

    // - position color buffer
    glGenTextures(1, &positionTextureID);
    glBindTexture(GL_TEXTURE_2D, positionTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionTextureID, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // - normal color buffer
    glGenTextures(1, &normalTextureID);
    glBindTexture(GL_TEXTURE_2D, normalTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTextureID, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // - color + specular color buffer
    glGenTextures(1, &albedoTextureID);
    glBindTexture(GL_TEXTURE_2D, albedoTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, albedoTextureID, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, attachments);

    // Depth buffer
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Failed to create GBuffer Framebuffer" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::destroy()
{
    glDeleteTextures(1, &positionTextureID);
    glDeleteTextures(1, &albedoTextureID);
    glDeleteTextures(1, &normalTextureID);
    glDeleteTextures(1, &depthTexture);
    glDeleteFramebuffers(1, &fboID);
}
