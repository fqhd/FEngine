#include <iostream>
#include "FEngine.hpp"

int main()
{
    FEngine engine("Window", 800, 600);
    FObject cube = engine.loadObject("res/cube");

    engine.objects.push_back(cube);

    engine.camera.position.z = -10;
    engine.camera.position.y = 5;
    engine.camera.yaw = 90;
    engine.camera.pitch = -20;

    while (engine.window.isOpen())
    {
        engine.objects[0].transform.rotation.x += 1;
        engine.objects[0].transform.rotation.z += 1;
        engine.draw();
    }

    engine.destroy();

    return 0;
}