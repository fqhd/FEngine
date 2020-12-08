#ifndef GAME_H
#define GAME_H

#include "Engine.hpp"
#include "GameStates.hpp"
#include "World.hpp"

class Game {
public:

     void init(Settings& settings);
     void update(InputManager& manager, Settings& settings, GameStates& state);
     void render();
     void destroy();

     void loadLevel(Settings& settings);

private:


     //Game functions
     void addEntities();

     //Game Objects
     Engine m_engine;
     World m_world;

     //Game Variables
     std::vector<Entity> m_entities;

};

#endif
