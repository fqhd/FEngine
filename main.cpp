#include "Camera3D.hpp"
#include "MasterRenderer.hpp"
#include "Window.hpp"

void update();
void render();

int main(int argc, char** argv){


     //Engine Objects
     Window window;



     //Initing game objects
     window.create(800, 600, "Game Engine");


     while(!window.isCloseRequested()){
          window.clear();

          update();
          render();

          window.update();
     }

     //Destroying game objects
     window.close();


     return 0;
}

void update(){

}

void render(){

}
