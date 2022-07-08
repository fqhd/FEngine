#include <iostream>
#include "FEngine.hpp"

int main()
{
    FEngine engine("Window", 1280, 720);
    FObject cube = engine.loadObject("res/cube", Color(255, 255, 255));
    FObject plane = engine.loadObject("res/plane", Color(170, 180, 190));

    engine.objects.push_back(cube);
    engine.objects.push_back(plane);

    engine.objects[0].transform.position.y = 2;

    engine.camera.position.z = -30;
    engine.camera.position.y = 8;
    engine.camera.yaw = 90;
    engine.camera.pitch = -20;

    while (engine.window.isOpen())
    {
        engine.camera.position.z -= 0.1;
        engine.objects[0].transform.rotation.x += 1;
        engine.objects[0].transform.rotation.z += 1;
        engine.draw();
    }

    engine.destroy();

    return 0;
}