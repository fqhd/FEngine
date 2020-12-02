#include "Window.hpp"
#include "GameStates.hpp"
#include "InputManager.hpp"
#include "Settings.hpp"

int main(){

     //Game Variables
     Window window;
     GameStates state;
     InputManager manager;
     Settings settings;

     //Initializing game variables
     settings.loadFromFile();
     window.create(settings);


     //Gameloop
     while(state != GameStates::EXIT){
          manager.processInput(window.window, state);
          window.clear();


          window.update();
     }



     //Cleanup
     window.close();


     return 0;
}
