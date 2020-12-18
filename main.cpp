#include "Camera3D.hpp"
#include "MasterRenderer.hpp"
#include "Window.hpp"
#include "Camera3D.hpp"
#include "Settings.hpp"


void update();
void render();

int main(int argc, char** argv){


     //Engine Objects
     Settings settings;
     Window window;
     MasterRenderer renderer;



     //Initing game objects
     settings.loadFromFile("res/settings.txt");
     window.create(settings.screenWidth, settings.screenHeight, "Game Engine");
     renderer.init(settings.screenWidth, settings.screenHeight);

     while(!window.isCloseRequested()){
          window.clear();

          update();
          render();

          window.update();
     }

     //Destroying game objects
     settings.writeToFile("res/settings.txt");
     window.close();


     return 0;
}

void update(){

}

void render(){

}
