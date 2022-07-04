#pragma once

#include <vector>

#include "FEngine/Camera/FirstPersonCamera.hpp"
#include "Camera/ThirdPersonCamera.hpp"
#include "Fengine/Utils/Window.hpp"
#include "FEngine/Renderer/Entity.hpp"
#include "Assets.hpp"
#include "FEngine/SSAO/SSAO.hpp"
#include "../Skybox/Skybox.hpp"
#include "../Renderer/DynamicEntityRenderer.hpp"
#include "../Terrain/StaticTerrain.hpp"
#include "../Terrain/DynamicTerrain.hpp"

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




};
