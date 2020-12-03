#include "Window.hpp"
#include "GameStates.hpp"
#include "InputManager.hpp"
#include "Settings.hpp"
#include "GUIRenderer.hpp"
#include "GUIShader.hpp"
#include "GUIImage.hpp"
#include "Camera2D.hpp"
#include "GUIAssets.hpp"

int main(){

     //Game Variables
     Window window;
     GameStates state;
     InputManager manager;
     Settings settings;
     GUIRenderer renderer;
     GUIShader shader;
     GUIImage image;
     Camera2D camera;
     GUIAssets assets;

     //Initializing game variables
     settings.loadFromFile();
     window.create(settings);
     renderer.init();
     shader.loadShader("res/shaders/gui_vertex_shader.glsl", "res/shaders/gui_fragment_shader.glsl");
     camera.createProjectionMatrix(settings);
     assets.init();

     //Gameloop
     while(state != GameStates::EXIT){
          manager.processInput(window.window, state);
          window.clear();

          shader.bind();

          shader.loadMatrix(camera.getProjectionMatrix());
          renderer.begin();
          renderer.draw(glm::vec4(10, 10, 200, 200), glm::vec4(0, 0, 1, 1), assets.getBlankTextureID(), 0.0f, ColorRGBA8());
          renderer.end();
          renderer.renderBatch();

          shader.unbind();


          window.update();
     }

     //Cleanup
     settings.writeToFile();
     window.close();


     return 0;
}
