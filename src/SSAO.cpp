#include "SSAO.hpp"
#include <random>

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

void SSAO::init(Window *win)
{
    window = win;
    shader.init("res/shaders/ssao");
    shader.bind();
    shader.set("gPosition", 0);
    shader.set("gNormal", 1);
    shader.set("texNoise", 2);
    quad.init();
    noiseTexture.init();
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glm::ivec2 size = window->getFramebufferSize();
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.x, size.y, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FB error, status: 0x" << Status << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // random floats between [0.0, 1.0]
    std::default_random_engine generator;
    for (unsigned int i = 0; i < 64; ++i)
    {
        glm::vec3 sample(
            randomFloats(generator) * 2.0 - 1.0,
            randomFloats(generator) * 2.0 - 1.0,
            randomFloats(generator));
        sample = glm::normalize(sample);
        sample *= randomFloats(generator);
        float scale = (float)i / 64.0;
        scale = lerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        ssaoKernel.push_back(sample);
    }
}

void SSAO::draw(DeferredRenderer &renderer, Camera *camera)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    shader.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.positionTextureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, renderer.gbuffer.normalTextureID);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, noiseTexture.textureID);
    glm::ivec2 windowSize = window->getFramebufferSize();
    shader.set("screenWidth", windowSize.x);
    shader.set("screenHeight", windowSize.y);
    shader.set("view", camera->getView());
    shader.set("kernelSize", (int)ssaoKernel.size());
    shader.set("projection", camera->getProjection());
    for (unsigned int i = 0; i < ssaoKernel.size(); i++)
    {
        shader.set("samples[" + std::to_string(i) + "]", ssaoKernel[i]);
    }
    quad.draw();
    shader.unbind();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAO::destroy()
{
    // TODO Fill this.
}