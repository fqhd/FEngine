#pragma once

class Settings{
public:

     void loadFromFile();
     void writeToFile();

     //Defaults
     unsigned int screenWidth = 1280;
     unsigned int screenHeight = 720;

}
