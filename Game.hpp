#ifndef GAME_H
#define GAME_H

#include "EntityHandler.hpp"
#include "Engine.hpp"


class Game {
public:

     void init(Settings& settings);
     void update(InputManager& manager, Settings& settings);
     void render();
     void destroy();


private:

     //Game functions
     void addEntities();


     Engine m_engine;
     EntityHandler m_entityHandler;

};

#endif
