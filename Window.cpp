#include "Window.hpp"
#include <string>


void Window::create(unsigned int width, unsigned int height, const std::string& name, bool resizable, bool decorated){

     if(!glfwInit()){
          Utils::log("Failed to initialize GLFW");
     }


     //Setting Window settings
     glfwWindowHint(GLFW_RED_BITS, 8);
     glfwWindowHint(GLFW_GREEN_BITS, 8);
     glfwWindowHint(GLFW_BLUE_BITS, 8);
     glfwWindowHint(GLFW_ALPHA_BITS, 8);
     glfwWindowHint(GLFW_DEPTH_BITS, 24);
     glfwWindowHint(GLFW_STENCIL_BITS, 8);
     glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     if (!resizable) glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
     if (!decorated) glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

#ifdef __APPLE__
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
     if (!resizable) glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
     if (!decorated) glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

     //Creating the window
     window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
     if(!window){
          Utils::log("Window: Failed to create window");
     }

     //Settings for window
     glfwSwapInterval(1);

     //Creating the context for opengl
     glfwMakeContextCurrent(window);

     //Initializing glew
     if(glewInit() != GLEW_OK){
          Utils::log("Window: Failed to initialize glew");
     }

     //Enabling transparency
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     //Enabling depth
     glEnable(GL_DEPTH_TEST);
     glClearDepthf(1.0f);

     //Enabling back face culling
     glEnable(GL_CULL_FACE);
     glCullFace(GL_BACK);


     InputManager::init(window);


}

void Window::clear(){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update(){
     glfwSwapBuffers(window);
     m_closeRequested = InputManager::processInput(window);
     //optional code exit method
     if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)) {
          m_closeRequested = true;
     }
}

void Window::close(){
     glfwDestroyWindow(window);
     glfwTerminate();
}

bool Window::isCloseRequested(){
     return m_closeRequested;
}
