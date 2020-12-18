#include "Camera3D.hpp"
#include "MasterRenderer.hpp"
#include "Window.hpp"
#include "Camera3D.hpp"
#include "Assets.hpp"

constexpr unsigned int SCREEN_WIDTH = 1280;
constexpr unsigned int SCREEN_HEIGHT = 720;

int main(int argc, char** argv){

     //Engine Objects
     Window window;
     MasterRenderer renderer;
     Assets assets;
     Camera3D camera;

     //Initializing game objects
     window.create(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Engine");
     renderer.init(SCREEN_WIDTH, SCREEN_HEIGHT);
     camera.init(SCREEN_WIDTH, SCREEN_HEIGHT);
     assets.init();

     //Initializing engine parameters
     renderer.batchRenderingEnabled = true;
     renderer.skyboxEnabled = true;


     //Game objects
     std::vector<Entity> entities;

     //Initializing game objects
     entities.emplace_back(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), assets.getPlayerModel(), assets.getPlayerTexture());

     while(!window.isCloseRequested()){
          window.clear();

          //Updating
          camera.update();

          //Rendering
          renderer.renderScene(entities, camera, assets.getSkyTexture());


          window.update();
     }

     //Destroying game objects
     window.close();


     return 0;
}
