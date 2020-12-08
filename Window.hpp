#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "Settings.hpp"


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
