#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

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

class MasterRenderer {
public:

     void init(Settings& settings);
     void renderScene(std::vector<Entity>& entities, Camera3D& camera, Assets& assets);
     void destroy();

     BatchRenderer batchRenderer;

private:

     //Functions
     void renderEntities(std::vector<Entity>& entities);
     void renderSkybox(Camera3D& camera, Assets& assets);
     void renderObjects(std::vector<Entity>& entities, Camera3D& camera);
     void renderSSAOQuad();

     //Objects
     GBuffer m_gbuffer;
     Quad m_quad;
     Cube m_cube;

     //Shaders
     GBufferShader m_gbufferShader;
     CubemapShader m_cubemapShader;
     SSAOShader m_ssaoShader;

};
#endif
