#ifndef ASSETS_H
#define ASSETS_H

#include "Model.hpp"
#include "Texture.hpp"

class Assets {
public:

     void init();

     //Model Getters
     Model* getPlayerModel();

     //Texture getters
     Texture* getPlayerTexture();
     Texture* getGrassTexture();

     void destroy();



private:

     //Inits
     void initModels();
     void initTextures();

     //Destroys
     void destroyModels();
     void destroyTextures();

     //Models
     Model m_playerModel;

     //Textures
     Texture m_playerTexture;
     Texture m_grassTexture;

};

#endif
