#ifndef GAME_H
#define GAME_H

#include "EntityHandler.hpp"
#include "Camera3D.hpp"
#include "Settings.hpp"
#include "Surface.hpp"
#include "BatchRenderer.hpp"
#include "ModelShader.hpp"

class Game {
public:

     void init(Settings& settings);
     void update();
     void render();
     void destroy();


private:

     EntityHandler m_entityHandler;
     BatchRenderer m_batchRenderer;
     ModelShader m_shader;

     Camera3D m_camera;
     Surface m_surface;

};

#endif
