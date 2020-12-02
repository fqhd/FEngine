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

     unsigned int getWidth();
     unsigned int getHeight();

private:

     unsigned int m_width = 0;
     unsigned int m_height = 0;

};
