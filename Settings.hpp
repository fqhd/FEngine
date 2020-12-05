#ifndef SETTINGS_H
#define SETTINGS_H

class Settings{
public:

     //Useful functions
     void loadFromFile();
     void writeToFile();

     //Defaults
     unsigned int screenWidth = 1280;
     unsigned int screenHeight = 720;
     unsigned int sliderButtonWidth = 7;
     unsigned int sliderButtonHeight = 16;
     
};
#endif
