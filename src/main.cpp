#include <iostream>
#include "FEngine.hpp"

int main(){
    FEngine engine("Window", 800, 600);
    // FObject object = renderer.loadObject("res/cube")
    
    while(engine.window.isOpen()){

        engine.draw();
    }

	return 0;
}