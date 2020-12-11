#include "World.hpp"


char World::getTile(int x, int z, unsigned int worldWidth){
     if(x >= 0 && x < worldWidth && z >= 0 && z < worldWidth){
          return m_tiles[z * worldWidth + x];
     }
     return 0;
}

void World::setTile(int x, int z, char tile, unsigned int worldWidth){
     if(x >= 0 && x < worldWidth && z >= 0 && z < worldWidth){
          m_tiles[z * worldWidth + x] = tile;
     }
}

bool World::loadWorld(unsigned int level){

     if(m_tiles){
          delete[] m_tiles;
     }

     std::ifstream is;
     is.open("res/worlds/" + std::to_string(level) + ".txt");
     if(is.fail()){
          Utils::log(DISK, "World: Failed to load world: " + std::to_string(level));
          return false;
     }

     std::vector<std::string> data;
     std::string line;
     while(std::getline(is, line)) {
          data.push_back(line);
     }
     is.close();

     m_width = data.size();

     if(data.size() == data[0].size()){
          m_tiles = new char[(data.size()+1) * (data[0].size() + 1)];

          for(unsigned int i = 0; i < data.size(); i++){
               for(unsigned int j = 0; j < data[i].size(); j++){
                    m_tiles[i * m_width + j] = data[i][j];
               }
          }

          return true;
     }

     Utils::log(DISK, "World: Failed to load world: " + std::to_string(level));
     Utils::log(DISK, "World: Wrong file number");
     return false;
}

unsigned int World::getWidth(){
     return m_width;
}

void World::destroy(){
     if(m_tiles){
          delete[] m_tiles;
     }
}
