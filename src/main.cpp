#include <iostream>
#include "FEngine.hpp"

int main()
{
    FEngine engine("Window", 800, 600);
    FObject cube = engine.loadObject("res/cube", Color(255, 255, 255));
    FObject plane = engine.loadObject("res/plane", Color(170, 180, 190));

    engine.objects.push_back(cube);
    engine.objects.push_back(plane);

    engine.objects[0].transform.position.y = 2;
    engine.objects[0].transform.position.x = -10;
    engine.objects[0].transform.position.z = 5;
    engine.objects[1].transform.scale = glm::vec3(10);

    engine.camera.position.z = -5;
    engine.camera.position.y = 6;
    engine.camera.yaw = 90;
    engine.camera.pitch = -15;
    
    float speed = 0.2;
    while (engine.window.isOpen())
    {
        if(engine.inputManager.isKeyDown(GLFW_KEY_W)){
            engine.camera.position.z += speed;
        }
        if(engine.inputManager.isKeyDown(GLFW_KEY_A)){
            engine.camera.position.x += speed;
        }
        if(engine.inputManager.isKeyDown(GLFW_KEY_S)){
            engine.camera.position.z -= speed;
        }
        if(engine.inputManager.isKeyDown(GLFW_KEY_D)){
            engine.camera.position.x -= speed;
        }
        if(engine.inputManager.isKeyDown(GLFW_KEY_SPACE)){
            engine.camera.position.y += speed;
        }
        if(engine.inputManager.isKeyDown(GLFW_KEY_LEFT_SHIFT)){
            engine.camera.position.y -= speed;
        }

        if(engine.inputManager.isKeyDown(GLFW_KEY_UP)){
            engine.camera.pitch += speed * 7.0;
        }
        if(engine.inputManager.isKeyDown(GLFW_KEY_DOWN)){
            engine.camera.pitch -= speed * 7.0;
        }
        if(engine.inputManager.isKeyDown(GLFW_KEY_RIGHT)){
            engine.camera.yaw += speed * 7.0;
        }
        if(engine.inputManager.isKeyDown(GLFW_KEY_LEFT)){
            engine.camera.yaw -= speed * 7.0;
        }

        engine.objects[0].transform.rotation.y -= 1;
        engine.draw();
    }

    engine.destroy();

    return 0;
}