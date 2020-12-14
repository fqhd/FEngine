#include "Game.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "Settings.hpp"
#include "GameStates.hpp"
#include "Menu.hpp"


int main(int argc, char** argv){

     //Program Objects
     Window window;
     Settings settings;
     GameStates state;
     Game game;
     Menu menu;

     //Program Inits
     settings.loadFromFile();
     window.create(settings);
     state = GameStates::PLAY;
     game.init(settings);
     InputManager::init(window.window);

     while(state != GameStates::EXIT){


          while(state == GameStates::PLAY){
               window.clear();
               InputManager::processInput(window.window, state, settings);

               game.update(settings, state);
               game.render();

               window.update();
          }
          while(state == GameStates::MENU){
               window.clear();
               InputManager::processInput(window.window, state, settings);

               menu.update(settings, state);
               menu.render();

               window.update();
          }
     }

     game.destroy();
     menu.destroy();
     window.close();


     return 0;
}
