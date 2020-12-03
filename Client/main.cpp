
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
#include "GUICheckbox.hpp"

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
     GUICheckbox checkbox(glm::vec4(200, 30, 16, 16), ColorRGBA8(0, 255, 0, 255), ColorRGBA8(50, 50, 50, 50), false);

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
          checkbox.update(manager);

          //Rendering
          shader.bind();

          shader.loadMatrix(camera.getProjectionMatrix());
          renderer.begin();

          checkbox.render(renderer, assets.getBlankTextureID());


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
