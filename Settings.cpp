#include "Settings.hpp"
#include <fstream>

void Settings::writeToFile(){

     std::ofstream os;
     os.open("config.txt");

     os << "ScreenWidth: " << screenWidth << std::endl;
     os << "ScreenHeight: " << screenHeight << std::endl;
     os << "MouseSensitivty: " << mouseSensitivity << std::endl;
     os << "ZoomSensitivty: " << zoomSensitivity << std::endl;
     os << "CurrentWorld: " << currentWorld << std::endl;
     os << "CameraSensitivity: " << cameraSensitivity << std::endl;

     os.close();


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
          }else if(name == "MouseSensitivty:"){
               is >> mouseSensitivity;
          }else if(name == "ZoomSensitivty:"){
               is >> zoomSensitivity;
          }else if(name == "CurrentWorld:"){
               is >> currentWorld;
          }else if(name == "CameraSensitivity:"){
               is >> cameraSensitivity;
          }
     }
     is.close();
}
