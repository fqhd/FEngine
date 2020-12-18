#include "Assets.hpp"

void Assets::init(){
     initModels();
     initTextures();
}



void Assets::initModels(){
     m_playerModel.loadFromFile("res/models/player.obj");
}

void Assets::initTextures(){

     //Adding cubemap sky texture
     std::vector<std::string> faces;
     faces.push_back("res/textures/sky/bottom.png");
     faces.push_back("res/textures/sky/front.png");
     faces.push_back("res/textures/sky/top.png");
     faces.push_back("res/textures/sky/back.png");
     faces.push_back("res/textures/sky/right.png");
     faces.push_back("res/textures/sky/left.png");
     m_skyTexture.loadFromFile(faces);

     //Adding normal entity textures
     m_playerTexture.init("res/textures/player_texture.jpg");


}

//Model Getters
Model* Assets::getPlayerModel() {
     return &m_playerModel;
}


//Texture getters
CubeTexture* Assets::getSkyTexture() {
     return &m_skyTexture;
}

Texture* Assets::getPlayerTexture(){
     return &m_playerTexture;
}


void Assets::destroy(){
     destroyModels();
     destroyTextures();
}

void Assets::destroyModels(){
     m_playerModel.destroy();
}

void Assets::destroyTextures(){
     m_skyTexture.destroy();
     m_playerTexture.destroy();
}
