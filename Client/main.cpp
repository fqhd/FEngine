
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
#include "GUISlider.hpp"
#include "GUIFont.hpp"
#include <iostream>

int main(){



     //Game Variables
     Window window;
     GameStates state;
     InputManager manager;
     Settings settings;
     GUIRenderer renderer;
     GUIShader shader;
     Camera2D camera;
     GUIAssets assets;
     GUIFont font;

     //Initializing game variables
     settings.loadFromFile();
     window.create(settings);
     renderer.init();
     shader.loadShader("res/shaders/gui_vertex_shader.glsl", "res/shaders/gui_fragment_shader.glsl");
     camera.createProjectionMatrix(settings);
     assets.init();
     font.initFont();

     GUIImage image(glm::vec4(200, 200, 128, 128), assets.getBlankTextureID(), ColorRGBA8());
     GUISlider slider(glm::vec2(50, 50), 250.0f, ColorRGBA8(255, 0, 0, 255), ColorRGBA8(), 0.0f, settings);


     //Gameloop
     while(state != GameStates::EXIT){
          manager.processInput(window.window, state);
          window.clear();

          //Updating
          slider.update(manager, settings);



          //Preparing
          shader.bind();
          shader.loadMatrix(camera.getProjectionMatrix());
          renderer.begin();




          //Rendering
          slider.render(renderer, assets.getBlankTextureID());
          image.render(renderer);
          font.renderFont(renderer, 100.0f, 100.0f, "The quick brown fox jumped over the lazy dog");



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
