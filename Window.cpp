#include "Window.hpp"


void Window::create(Settings& settings){

     SDL_Init(SDL_INIT_EVERYTHING);

     //Setting Window settings
     SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
     SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
     SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

     //Creating the window
     m_window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings.screenWidth, settings.screenHeight, SDL_WINDOW_OPENGL);
     SDL_GL_SetSwapInterval(1);

     if(!m_window){
          Utils::log(CONSOLE, "Failed to create window");
     }

     SDL_GLContext context = SDL_GL_CreateContext(m_window);
     if(!context){
          Utils::log(CONSOLE, "Failed to create context for window");
     }

     //Initializing glew
     if(glewInit() != GLEW_OK){
          Utils::log(DISK, "Failed to initialize glew");
     }

     //OpenGL Callback Function
     glDebugMessageCallback(DebugOutputCallback, 0);
     glEnable(GL_DEBUG_OUTPUT);
     glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

     //Enabling transparency
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     //Enabling depth
     glEnable(GL_DEPTH_TEST);
     glClearDepthf(1.0f);

     //Enabling back face culling
     glEnable(GL_CULL_FACE);
     glCullFace(GL_BACK);

}

void Window::clear(){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update(){
     SDL_GL_SwapWindow(m_window);
}

void Window::close(){
     SDL_DestroyWindow(m_window);
     SDL_Quit();
}

void DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        printf("OpenGL Debug Output message : ");

        if (source == GL_DEBUG_SOURCE_API_ARB)                    printf("Source : API; ");
        else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)    printf("Source : WINDOW_SYSTEM; ");
        else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)    printf("Source : SHADER_COMPILER; ");
        else if (source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)        printf("Source : THIRD_PARTY; ");
        else if (source == GL_DEBUG_SOURCE_APPLICATION_ARB)        printf("Source : APPLICATION; ");
        else if (source == GL_DEBUG_SOURCE_OTHER_ARB)            printf("Source : OTHER; ");

        if (type == GL_DEBUG_TYPE_ERROR_ARB)                    printf("Type : ERROR; ");
        else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)    printf("Type : DEPRECATED_BEHAVIOR; ");
        else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)    printf("Type : UNDEFINED_BEHAVIOR; ");
        else if (type == GL_DEBUG_TYPE_PORTABILITY_ARB)            printf("Type : PORTABILITY; ");
        else if (type == GL_DEBUG_TYPE_PERFORMANCE_ARB)            printf("Type : PERFORMANCE; ");
        else if (type == GL_DEBUG_TYPE_OTHER_ARB)                printf("Type : OTHER; ");

        if (severity == GL_DEBUG_SEVERITY_HIGH_ARB)                printf("Severity : HIGH; ");
        else if (severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)        printf("Severity : MEDIUM; ");
        else if (severity == GL_DEBUG_SEVERITY_LOW_ARB)            printf("Severity : LOW; ");
        printf("Message : %s\n", message);
    }
}
