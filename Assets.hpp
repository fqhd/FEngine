#ifndef ASSETS_H
#define ASSETS_H

#include "Model.hpp"
#include "CubeTexture.hpp"

class Assets {
public:

     void init();

     //Model Getters
     Model* getPlayerModel();

     //Texture getters
     CubeTexture* getSkyTexture();

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
     CubeTexture m_skyTexture;

};

#endif
