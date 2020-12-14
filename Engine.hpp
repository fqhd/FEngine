#ifndef ENGINE_H
#define ENGINE_H

#include "InputManager.hpp"
#include "MasterRenderer.hpp"

class Engine {
public:


     void init(Settings& settings);
     void update(Settings& settings);
     void render(std::vector<Entity>& entities);
     void destroy();

     GUI gui;
     Assets assets;
     Camera3D camera3D;
     Camera2D camera2D;
     MasterRenderer masterRenderer;

private:

     void updateGUI();


};

#endif
