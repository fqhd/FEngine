#include "Game.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "Settings.hpp"
#include "GameStates.hpp"
#include "Menu.hpp"


int main(int argc, char** argv){

     //Program Objects
     Window window;
     InputManager manager;
     Settings settings;
     GameStates state;
     Game game;
     Menu menu;

     //Program Inits
     settings.loadFromFile();
     window.create(settings);
     state = GameStates::PLAY;
     game.init(settings);
     menu.init();

     while(state != GameStates::EXIT){


          while(state == GameStates::PLAY){
               window.clear();
               manager.processInput(state, settings);

               game.update(manager, settings, state);
               game.render();

               window.update();
          }
          while(state == GameStates::MENU){
               window.clear();
               manager.processInput(state, settings);

               menu.update(manager, settings, state);
               menu.render();

               window.update();
          }
     }

     game.destroy();
     menu.destroy();
     window.close();


     return 0;
}
