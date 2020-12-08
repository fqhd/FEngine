#include "Window.hpp"
#include <GL/glew.h>

#include "Utils.hpp"

void Window::create(Settings& settings){

     SDL_Init(SDL_INIT_EVERYTHING);

     //Setting Window settings
     SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
     SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
     SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

     //Creating the window
     m_window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings.screenWidth, settings.screenHeight, SDL_WINDOW_OPENGL);
     if(!m_window){
          Utils::log(CONSOLE, "Failed to create window");
     }

     SDL_GLContext context = SDL_GL_CreateContext(m_window);
     if(!context){
          Utils::log(CONSOLE, "Failed to create context for window");
     }

     //Initializing glew
     if(glewInit() != GLEW_OK){
          Utils::log(CONSOLE, "Failed to initialize glew");
     }


     //Enabling transparency
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     //Enabling depth ContextSettings
     glEnable(GL_DEPTH_TEST);

     //Enabling back face culling
     glEnable(GL_CULL_FACE);
     glCullFace(GL_BACK);

     //Enabling MSAA
     glEnable(GL_MULTISAMPLE);

}

void Window::clear(){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update(){
     SDL_GL_SwapWindow(m_window);
}

void Window::close(){
     SDL_DestroyWindow(m_window);
     SDL_Quit();
}
