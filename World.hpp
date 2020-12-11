#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <fstream>
#include <cstring>

#include "Utils.hpp"
#include "Entity.hpp"


class World {
public:


     bool loadWorld(unsigned int level);
     void destroy();
     char getTile(int x, int z, unsigned int worldWidth);
     void setTile(int x, int z, char tile, unsigned int worldWidth);

     unsigned int getWidth();


private:

     char* m_tiles = nullptr;
     unsigned int m_width = 0;

};

#endif
