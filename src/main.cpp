#include <iostream>
#include "FEngine.hpp"

int main()
{
    FEngine engine("Window", 1280, 720);
    FObject cube = engine.loadObject("res/cube", Color(255, 255, 255));
    FObject plane = engine.loadObject("res/plane", Color(170, 180, 190));

    engine.objects.push_back(cube);
    engine.objects.push_back(plane);

    engine.objects[0].transform.position.y = 1;
    engine.objects[1].transform.scale = glm::vec3(10000);

    engine.camera.position.z = -5;
    engine.camera.position.y = 3;
    engine.camera.yaw = 90;
    engine.camera.pitch = -10;

    while (engine.window.isOpen())
    {
        engine.objects[0].transform.rotation.y += 1;
        // engine.objects[0].transform.position.z += 0.5;
        engine.draw();
    }

    engine.destroy();

    return 0;
}