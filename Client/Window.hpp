#pragma once
#include <SFML/Window.hpp>
#include "Settings.hpp"

class Window {
public:

     void create(Settings& settings);
     void clear();
     void update();
     void close();

     sf::Window window;


private:


};
