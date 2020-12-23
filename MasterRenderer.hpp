#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include "SSAO.hpp"
#include "Skybox.hpp"
#include "DynamicEntityRenderer.hpp"
#include "StaticTerrain.hpp"

class MasterRenderer {
public:

     void init(unsigned int width, unsigned int height);
     void renderScene(std::vector<Entity>& entities, Camera& camera);
     void destroy();


private:

     //Objects



};

#endif
