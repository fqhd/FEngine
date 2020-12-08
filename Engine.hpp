#ifndef ENGINE_H
#define ENGINE_H

#include "Settings.hpp"
#include "InputManager.hpp"
#include "Assets.hpp"
#include "Cubemap.hpp"
#include "MasterRenderer.hpp"
#include "Camera3D.hpp"

class Engine {
public:


     void init(Settings& settings);
     void update(InputManager& manager, Settings& settings);
     void render(std::vector<Entity>& entities);
     void destroy();

     Assets assets;
     Camera3D camera;
     Cubemap cubemap;
     MasterRenderer masterRenderer;


private:




};

#endif
