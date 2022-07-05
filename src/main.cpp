#include <iostream>
#include "FEngine.hpp"

int main()
{
    FEngine engine("Window", 800, 600);
    FObject object = engine.loadObject("res/cube");
    engine.camera.position.z = -10;
    engine.camera.position.y = 5;
    engine.camera.yaw = 90;
    engine.camera.pitch = -20;

    while (engine.window.isOpen())
    {
        object.transform.rotation.x += 1;
        object.transform.rotation.z += 1;
        engine.draw(&object, 1);
    }

    return 0;
}