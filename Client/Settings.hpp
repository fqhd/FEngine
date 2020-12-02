#pragma once

class Settings{
public:

     //Useful functions
     void loadFromFile();
     void writeToFile();

     //Defaults
     unsigned int screenWidth = 1280;
     unsigned int screenHeight = 720;

};
