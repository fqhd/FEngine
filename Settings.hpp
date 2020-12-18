#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>
#include <string>


class Settings{
public:

     //Useful functions
     void loadFromFile(const std::string& path);
     void writeToFile(const std::string& path);

     //Defaults
     unsigned int screenWidth = 1280;
     unsigned int screenHeight = 720;
     float verticalSensitivity = 0.3f;
     float horizontalSensitivity = 0.3f;
     float zoomSensitivity = 0.5f;
     float cameraSpeed = 0.5f;


};
#endif
