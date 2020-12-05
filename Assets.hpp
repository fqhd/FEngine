#ifndef ASSETS_H
#define ASSETS_H

#include "Model.hpp"

class Assets {
public:

     void init();

     //Getters
     Model* getPlayerModel();



private:

     //Actual Models
     Model m_playerModel;

};

#endif
