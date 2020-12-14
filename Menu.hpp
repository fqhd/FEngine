#ifndef MENU_H
#define MENU_H

#include "InputManager.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"


class Menu {
public:

     void init();
     void update(Settings& settings, GameStates& state);
     void render();
     void destroy();

private:



};

#endif
