#include "Window.hpp"
#include <GL/glew.h>

void Window::create(const char* title){
     sf::ContextSettings settings;
     window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close, settings);
     m_width = width;
     m_height = height;
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

unsigned int Window::getWidth(){
     return m_width;
}

unsigned int Window::getHeight(){
     return m_height;
}
