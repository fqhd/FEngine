
#include "Settings.hpp"


void Settings::writeToFile(const std::string& path){

     std::ofstream os;
     os.open(path.c_str());

     os << "ScreenWidth: " << screenWidth << std::endl;
     os << "ScreenHeight: " << screenHeight << std::endl;
     os << "VerticalSensitivity: " << verticalSensitivity << std::endl;
     os << "HorizontalSensitivity: " << horizontalSensitivity << std::endl;
     os << "ZoomSensitivty: " << zoomSensitivity << std::endl;
     os << "CameraSpeed: " << cameraSpeed << std::endl;

     os.close();


}

void Settings::loadFromFile(const std::string& path){
     std::ifstream is;
     std::string name;
     is.open("config.txt");
     while(is >> name){
          if(name == "ScreenWidth:"){
               is >> screenWidth;
          }else if(name == "ScreenHeight:"){
               is >> screenHeight;
          }else if(name == "VerticalSensitivity:"){
               is >> verticalSensitivity;
          }else if(name == "HorizontalSensitivity:"){
               is >> horizontalSensitivity;
          }else if(name == "ZoomSensitivty:"){
               is >> zoomSensitivity;
          }else if(name == "CameraSpeed:"){
               is >> cameraSpeed;
          }
     }
     is.close();
}
