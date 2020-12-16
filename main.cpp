#include "Engine.hpp"


int main(int argc, char** argv){

     Engine engine;

     engine.init(800, 600, "Window");


     while(!engine.window.isCloseRequested()){

          engine.processInput();
          engine.update();
          engine.render();

     }

     engine.destroy();

     return 0;
}
