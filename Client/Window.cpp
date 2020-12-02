#include "Window.hpp"
#include <GL/glew.h>

void Window::create(Settings& settings){
     sf::ContextSettings cSettings;
     window.create(sf::VideoMode(settings.screenWidth, settings.screenHeight), "Sokuban", sf::Style::Titlebar | sf::Style::Close, cSettings);
}

void Window::clear(){
     glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update(){
     window.display();
}

void Window::close(){
     window.close();
}
