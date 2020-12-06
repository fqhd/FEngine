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
#include "Game.hpp"
#include "Menu.hpp"
#include <iostream>

int main(){



     //Game Variables
     Window window;
     GameStates state;
     InputManager manager;
     Settings settings;
     GUIAssets assets;
     Game game;
     Menu menu;


     //Initializing game variables
     state = GameStates::PLAY;
     settings.loadFromFile();
     window.create(settings);
     assets.init();
     game.init(settings);
     menu.init(settings);



     //Gameloop
     while(state != GameStates::EXIT){


          while(state == GameStates::MENU){
               manager.processInput(window.window, state);
               window.clear();

               menu.update();
               menu.render();

               window.update();
          }

          while(state == GameStates::PLAY){
               manager.processInput(window.window, state);
               window.clear();

               game.update(manager);
               game.render();

               window.update();
          }



          window.update();
     }

     //Saving Changes
     settings.writeToFile();

     //Cleanup
     menu.destroy();
     game.destroy();
     window.close();


     return 0;
}
