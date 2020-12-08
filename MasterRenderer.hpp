#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include "Camera3D.hpp"
#include "BatchRenderer.hpp"
#include "Entity.hpp"
#include "StaticShader.hpp"
#include "Settings.hpp"

class MasterRenderer {
public:

     void init(Settings& settings);
     void renderScene(std::vector<Entity>& entities, Camera3D& camera);
     void destroy();


private:

     //Static Object functions
     void addStaticObjects(Settings& settings);
     void addSurface(Settings& settings, StaticColor color);

     void renderEntities(std::vector<Entity>& entities);

     BatchRenderer m_batchRenderer;
     StaticShader m_staticShader;

};
#endif
