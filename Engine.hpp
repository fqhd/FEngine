#ifndef ENGINE_H
#define ENGINE_H

#include "Window.hpp"
#include "InputManager.hpp"
#include "MasterRenderer.hpp"


class Engine {
public:


     void init(unsigned int screenWidth, unsigned int screenHeight, const std::string& name);
     void update();
     void render();
     void destroy();
     void processInput();

     GUI gui;
     Assets assets;
     Camera3D camera3D;
     Camera2D camera2D;
     MasterRenderer masterRenderer;
     Window window;

     

private:

     void updateGUI();


};

#endif
