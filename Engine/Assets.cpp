#include "Assets.hpp"

void Assets::init(){
     initModels();
     initTextures();
}

void Assets::initModels(){
     m_playerModel.loadFromFile("res/models/player.obj");
}

void Assets::initTextures(){
     m_playerTexture.init("res/textures/player_texture.jpg");
     m_grassTexture.init("res/textures/grass.png");
}


//Model Getters
Model* Assets::getPlayerModel() {
     return &m_playerModel;
}


//Texture getters
Texture* Assets::getPlayerTexture(){
     return &m_playerTexture;
}

Texture* Assets::getGrassTexture(){
     return &m_grassTexture;
}

void Assets::destroy(){
     destroyModels();
     destroyTextures();
}

void Assets::destroyModels(){
     m_playerModel.destroy();
}

void Assets::destroyTextures(){
     m_playerTexture.destroy();
}
