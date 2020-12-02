#include "Settings.hpp"
#include <fstream>

void Settings::writeToFile(){

}

void Settings::loadFromFile(){
     std::ifstream is;
     std::string name;
     is.open("config.txt");
     while(is >> name){
          if(name == "ScreenWidth:"){
               is >> screenWidth;
          }else if(name == "ScreenHeight:"){
               is >> screenHeight;
          }
     }
}
