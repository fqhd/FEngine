#include "Settings.hpp"
#include <fstream>

void Settings::writeToFile(){

     std::ofstream os;
     os.open("config.txt");

     os << "ScreenWidth: " << screenWidth << std::endl;
     os << "ScreenHeight: " << screenHeight << std::endl;
     os << "SliderButtonWidth: " << sliderButtonWidth << std::endl;
     os << "SliderButtonHeight: " << sliderButtonHeight << std::endl;
     os << "WorldWidth: " << worldWidth << std::endl;
     os << "MouseSensitivty: " << mouseSensitivity << std::endl;
     os << "ZoomSensitivty: " << zoomSensitivity << std::endl;
     os << "CurrentWorld: " << currentWorld << std::endl;

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
          }else if(name == "SliderButtonWidth:"){
               is >> sliderButtonWidth;
          }else if(name == "SliderButtonHeight:"){
               is >> sliderButtonHeight;
          }else if(name == "WorldWidth:"){
               is >> worldWidth;
          }else if(name == "MouseSensitivty:"){
               is >> mouseSensitivity;
          }else if(name == "ZoomSensitivty:"){
               is >> zoomSensitivity;
          }else if(name == "CurrentWorld:"){
               is >> currentWorld;
          }
     }
     is.close();
}
