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
     unsigned int currentWorld = 0;
     float mouseSensitivity = 0.5f;
     float zoomSensitivity = 0.5f;

};
#endif
