#include <iostream>
#include "FEngine.hpp"

int main()
{
    FEngine engine("Window", 800, 600);
    FObject cube = engine.loadObject("res/cube", Color(255, 255, 255));
    FObject plane = engine.loadObject("res/plane", Color(170, 180, 190));

    engine.objects.push_back(cube);
    engine.objects.push_back(plane);

    engine.objects[0].transform.position.y = 10;

    engine.camera.position.z = -30;
    engine.camera.position.y = 15;
    engine.camera.yaw = 90;
    engine.camera.pitch = -30;

    while (engine.window.isOpen())
    {
        engine.camera.position.z -= 0.2;
        engine.objects[0].transform.rotation.x += 1;
        engine.objects[0].transform.rotation.z += 1;
        engine.draw();
    }

    engine.destroy();

    return 0;
}