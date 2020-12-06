#include "Assets.hpp"

void Assets::init(){
     initModels();
     initTextures();
}



void Assets::initModels(){
     m_playerModel.loadFromFile("res/models/player.obj");
}

void Assets::initTextures(){
     m_surfaceTexture.loadFromFile("res/textures/bricks.jpg");
}

//Model Getters
Model* Assets::getPlayerModel() {
     return &m_playerModel;
}


//Texture getters
Texture* Assets::getSurfaceTexture() {
     return &m_surfaceTexture;
}


void Assets::destroy(){
     destroyModels();
     destroyTextures();
}

void Assets::destroyModels(){
     m_playerModel.destroy();
}

void Assets::destroyTextures(){
     m_surfaceTexture.destroy();
}
