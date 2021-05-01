#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "FirstPersonCamera.hpp"
#include "ThirdPersonCamera.hpp"
#include "Window.hpp"
#include "Entity.hpp"
#include "Assets.hpp"
#include "SSAO.hpp"
#include "Skybox.hpp"
#include "DynamicEntityRenderer.hpp"
#include "StaticTerrain.hpp"
#include "DynamicTerrain.hpp"

///////////////////////////////////////////////////////////////////////
// THIS CLASS IS NOT PART OF THE ENEINGE
// THIS IS SIMPLY AN EXAMPLE OF HOW YOU COULD USE THE ENGINE
// IF YOU WOULD LIKE TO USE THE ENGINE, MAKE YOUR OWN CLASS OR USE THIS ONE AS A TEMPLATE/GUI
///////////////////////////////////////////////////////////////////////


class Engine {
public:

     void init(unsigned int width, unsigned int height, const std::string& name, bool resizable, bool decorated);
     void update();
     void render();
     void destroy();

     //Engine Variables
     Window window;
     Camera camera;
     Assets assets;
     SSAO m_ssao;
     Skybox m_skybox;
     DynamicEntityRenderer m_dynamicEntityRenderer;
     DynamicTerrain m_dynamicTerrain;

     //Game variables
     std::vector<Entity> entities;

private:


     //Game variables



};

#endif
