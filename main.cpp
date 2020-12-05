#include "Window.hpp"
#include "GameStates.hpp"
#include "InputManager.hpp"
#include "Settings.hpp"
#include "GUIRenderer.hpp"
#include "GUIShader.hpp"
#include "GUIImage.hpp"
#include "Camera2D.hpp"
#include "GUIAssets.hpp"
#include "GUIButton.hpp"
#include "GUICheckbox.hpp"
#include "GUISlider.hpp"
#include "GUIFont.hpp"
#include <iostream>

int main(){



     //Game Variables
     Window window;
     GameStates state;
     InputManager manager;
     Settings settings;
     GUIAssets assets;


     //Initializing game variables
     state = GameStates::MENU;
     settings.loadFromFile();
     window.create(settings);
     assets.init();



     //Gameloop
     while(state != GameStates::EXIT){
          

          while(state == GameStates::MENU){
               manager.processInput(window.window, state);
               window.clear();

               
               window.update();
          }
          
          while(state == GameStates::PLAY){
               manager.processInput(window.window, state);
               window.clear();


               window.update();
          }
          


          window.update();
     }

     //Saving Changes
     settings.writeToFile();

     //Cleanup
     window.close();


     return 0;
}
