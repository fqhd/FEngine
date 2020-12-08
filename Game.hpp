#ifndef GAME_H
#define GAME_H

#include "EntityHandler.hpp"
#include "Camera3D.hpp"
#include "Settings.hpp"
#include "InputManager.hpp"
#include "Assets.hpp"
#include "Cubemap.hpp"
#include "MasterRenderer.hpp"

class Game {
public:

     void init(Settings& settings);
     void update(InputManager& manager, Settings& settings);
     void render();
     void destroy();


private:

     //Game functions
     void addEntities();

     Assets m_assets;
     Camera3D m_camera;
     EntityHandler m_entityHandler;
     MasterRenderer m_masterRenderer;
     Cubemap m_cubemap;

};

#endif
