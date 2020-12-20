#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <random>
#include <algorithm>

#include "Camera3D.hpp"
#include "Entity.hpp"
#include "GBuffer.hpp"
#include "GBufferShader.hpp"
#include "Quad.hpp"
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
#include "CubeTexture.hpp"
#include "BatchedMesh.hpp"


class MasterRenderer {
public:

     void init(unsigned int width, unsigned int height);
     void renderScene(std::vector<Entity>& entities, Camera3D& camera, CubeTexture* texture);
     void renderGUI(GUI& gui, Camera2D& camera);
     void destroy();

     bool skyboxEnabled = false;

private:

     //Functions
     void renderSkybox(Camera3D& camera, CubeTexture* assets);
     void renderObjects(std::vector<Entity>& entities, Camera3D& camera);
     void renderObjectsInstanced(std::vector<Entity>& entities, Camera3D& camera);
     void renderSSAOQuad(Camera3D& camera);
     void renderBlurQuad();
     void createKernelSamples();
     float lerp(float a, float b, float f);
     void createSSAONoiseTexture(unsigned int width, unsigned int height);
     void renderSSAOLightingQuad();
     static bool compare(Entity a, Entity b);


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
     std::mt19937 m_generator;


};
#endif
