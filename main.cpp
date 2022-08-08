#include <iostream>
#include <FEngine/FEngine.hpp>

int main()
{
    FEngine engine("Window", 800, 600);
    FObject cube = engine.getObject("../res/cube", Color(255, 255, 255));
    FObject cube2 = engine.getObject("../res/cube", Color(255, 255, 255));
    FObject plane = engine.getObject("../res/plane", Color(170, 180, 190));

    cube.transform.position.y = 2;
    cube.transform.position.x = -10;
    cube.transform.position.z = 5;
    plane.transform.scale = glm::vec3(10);

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

        cube.transform.rotation.y -= 1;
        engine.draw(cube);
        engine.draw(cube2);
        engine.draw(plane);

        engine.update();
    }

    engine.destroy();

    return 0;
}