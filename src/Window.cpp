#include <FEngine/Window.hpp>
#include <iostream>

namespace FEngine
{
    void Window::create(unsigned int _width, unsigned int _height, const char *_title)
    {
        // Initializing GLFW
        if (!glfwInit())
        {
            std::cout << "Failed to initialize GLFW" << std::endl;
            return;
        }

        // Setting window hints
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
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // Creating the window
        m_window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
        if (!m_window)
        {
            std::cout << "Failed to create window" << std::endl;
            return;
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
        }

        // Vsync
        glfwSwapInterval(1);

        // Enabling depth
        glEnable(GL_DEPTH_TEST);
        glClearDepth(1.0);

        // Enabling back face culling
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // We need to do this for the skybox to work
        glDepthFunc(GL_LEQUAL);

        // Enable MSAA
        glEnable(GL_MULTISAMPLE);

        // Caching the framebuffer size
        int x, y;
        glfwGetFramebufferSize(m_window, &x, &y);
        framebufferSize = glm::ivec2(x, y);
    }

    GLFWwindow *Window::getWindowPtr()
    {
        return m_window;
    }

    bool Window::isOpen()
    {
        return !glfwWindowShouldClose(m_window);
    }

    void Window::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glm::ivec2 Window::getFramebufferSize()
    {
        return framebufferSize;
    }

    void Window::update()
    {
        glfwSwapBuffers(m_window);
    }

    void Window::close()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::setMouseGrabbed(bool grabbed)
    {
        if (grabbed)
        {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}