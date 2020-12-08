#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <fstream>
#include <cstring>

#include "Utils.hpp"
#include "Entity.hpp"
#include "Settings.hpp"


class World {
public:


     bool loadWorld(Settings& settings);
     void update(std::vector<Entity>& entities);
     void destroy();
     char getTile(int x, int z, unsigned int worldWidth);


private:

     char* m_tiles = nullptr;

};

#endif
