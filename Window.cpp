#include "Window.hpp"
#include <GL/glew.h>

void Window::create(Settings& settings){

     //Setting Window settings
     sf::ContextSettings cSettings;

     //Creating the window
     window.create(sf::VideoMode(settings.screenWidth, settings.screenHeight), "Window",
                   sf::Style::Default, cSettings);
     window.setVerticalSyncEnabled(true);

     //Initializing glew
     glewInit();


     //Enabling transparency
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     //Enabling depth ContextSettings
     glEnable(GL_DEPTH_TEST);

     //Enabling back face culling
     glEnable(GL_CULL_FACE);
     glCullFace(GL_BACK);
}

void Window::clear(){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update(){
     window.display();
}

void Window::close(){
     window.close();
}
