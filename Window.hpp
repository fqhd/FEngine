#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Settings.hpp"
#include "Utils.hpp"


void DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

class Window {
public:

     void create(Settings& settings);
     void clear();
     void update();
     void close();

private:

     SDL_Window* m_window;


};
#endif
