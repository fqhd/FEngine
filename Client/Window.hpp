#pragma once
#include <SFML/Window.hpp>

class Window {
public:

     void create(unsigned int windowWidth, unsigned int windowHeight, const char* title);
     void clear();
     void update();
     void close();

     sf::Window window;

private:



};
