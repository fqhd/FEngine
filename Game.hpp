#ifndef GAME_H
#define GAME_H

#include "EntityHandler.hpp"
#include "Camera3D.hpp"
#include "Settings.hpp"
#include "StaticObjects.hpp"

class Game {
public:

     void init(Settings& settings);
     void update();
     void render();
     void destroy();


private:


     EntityHandler m_entityHandler;
     StaticObjects m_staticObjects;

     Camera3D m_camera;

};

#endif
