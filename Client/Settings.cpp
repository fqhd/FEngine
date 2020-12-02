#include "Settings.hpp"
#include <fstream>

void Settings::writeToFile(){

     std::ofstream os;
     os.open("config.txt");

     os << "ScreenWidth: " << screenWidth << std::endl;
     os << "ScreenHeight: " << screenHeight << std::endl;

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
          }
     }
     is.close();
}
