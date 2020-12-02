#pragma once
#include <SFML/Window.hpp>

class Window {
public:

     void create(unsigned int width, unsigned int height, const char* title);
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
