#include "Window.hpp"
#include <GL/glew.h>

void Window::create(Settings& settings){

     //Setting Window settings
     sf::ContextSettings cSettings;

     window.create(sf::VideoMode(settings.screenWidth, settings.screenHeight), "Window",
                   sf::Style::Fullscreen, cSettings);
     glewInit();

     glClearColor(0, 0, 1, 1);

     //Enabling transparency
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
