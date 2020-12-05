#include "Assets.hpp"

void Assets::init(){
     m_playerModel.loadFromFile("res/models/player.obj");
}

Model* Assets::getPlayerModel() {
     return &m_playerModel;
}

void Assets::destroy(){
     m_playerModel.destroy();
}
