#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <random>

#include "Camera3D.hpp"
#include "BatchRenderer.hpp"
#include "Entity.hpp"
#include "Settings.hpp"
#include "GBuffer.hpp"
#include "GBufferShader.hpp"
#include "Quad.hpp"
#include "Assets.hpp"
#include "SSAOShader.hpp"
#include "Cube.hpp"
#include "CubemapShader.hpp"
#include "SSAOTexture.hpp"
#include "SSAOBuffer.hpp"
#include "SSAOBlurBuffer.hpp"
#include "SSAOBlurShader.hpp"
#include "SSAOLightingShader.hpp"
#include "GUI.hpp"
#include "GUIRenderer.hpp"
#include "GUIShader.hpp"
#include "Camera2D.hpp"

class MasterRenderer {
public:

     void init(Settings& settings);
     void renderScene(std::vector<Entity>& entities, Camera3D& camera, Assets& assets);
     void renderGUI(GUI& gui, Camera2D& camera);
     void destroy();

     BatchRenderer batchRenderer;

private:

     //Functions
     void renderEntities(std::vector<Entity>& entities);
     void renderSkybox(Camera3D& camera, Assets& assets);
     void renderObjects(std::vector<Entity>& entities, Camera3D& camera);
     void renderSSAOQuad(Camera3D& camera);
     void renderBlurQuad();
     void createKernelSamples();
     float lerp(float a, float b, float f);
     void createSSAONoiseTexture(Settings& settings);
     void renderSSAOLightingQuad();

     //Objects
     GBuffer m_gbuffer;
     Quad m_quad;
     Cube m_cube;
     SSAOTexture m_noiseTexture;
     SSAOBuffer m_ssaoBuffer;
     SSAOBlurBuffer m_blurBuffer;
     GUIRenderer m_guiRenderer;

     //Shaders
     GBufferShader m_gbufferShader;
     CubemapShader m_cubemapShader;
     SSAOShader m_ssaoShader;
     SSAOBlurShader m_blurShader;
     SSAOLightingShader m_ssaoLightingShader;
     GUIShader m_guiShader;

     //Master Renderer Variables
     std::vector<glm::vec3> m_kernelSamples;
     std::mt19937 generator;


};
#endif
