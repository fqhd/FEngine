
#include "Window.hpp"
#include "GameStates.hpp"
#include "InputManager.hpp"
#include "Settings.hpp"
#include "GUIRenderer.hpp"
#include "GUIShader.hpp"
#include "GUIImage.hpp"
#include "Camera2D.hpp"
#include "GUIAssets.hpp"
#include "GUIButton.hpp"

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
     GUIButton button(glm::vec4(30, 30, 150, 30), ColorRGBA8());

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

          //Updating

          //Rendering
          shader.bind();

          shader.loadMatrix(camera.getProjectionMatrix());
          renderer.begin();

          renderer.end();
          renderer.renderBatch();

          shader.unbind();


          window.update();
     }

     //Saving Changes
     settings.writeToFile();

     //Cleanup
     renderer.dispose();
     shader.destroy();
     window.close();


     return 0;
}
