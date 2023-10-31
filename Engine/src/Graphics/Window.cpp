//
// Created by VrikkaDev on 26/09/2023.
//

#include "Window.h"
#include "Event/WindowEvent.h"
#include "Core/Threads/RenderThread.h"

namespace DuckEngine {
    std::vector<Window*> Window::m_Windows = {};

    Window::Window(uint32_t width, uint32_t height, const char* title) {
        // Initialize GLFW
        if(!glfwInit()){
            exit(EXIT_FAILURE);
        }

        // Set OpenGL version and profile to use
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create GLFW window with the specified dimensions and title
        m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

        // If window creation failed, terminate GLFW library and exit
        if (!m_Window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        // Set window callbacks
        glfwSetKeyCallback(m_Window, key_callback);
        glfwSetCursorPosCallback(m_Window, cursor_position_callback);
        glfwSetWindowSizeCallback(m_Window, resize_callback);

        // Sets window size limits, prevents crashing when trying to resize window into negative
        glfwSetWindowSizeLimits(m_Window, 40, 40, 3000, 3000);

        // Set GLFW window as the current OpenGL context
        glfwMakeContextCurrent(m_Window);
        // Load glad
        gladLoadGL();
        // Set VSync 1/0
        glfwSwapInterval(1);

        // Set the keyboard and mouse of this window
        keyboard = std::make_shared<Keyboard>(m_Window);
        mouse = std::make_shared<Mouse>(m_Window);

        // Push this window instance into the array of windows
        m_Windows.push_back(this);

        // Set the flag to indicate that the window is running
        IsRunning = true;

        m_WindowSize = {width, height};

        // Set the background color
        background_color = Color();
    }

    // Swap the front and back buffers, process events and update the IsRunning flag
    void Window::SwapBuffers() {
        // Swap the front and back buffers
        glfwSwapBuffers(m_Window);
        // Process any pending events such as input events
        glfwPollEvents();

        // Check if the window should close and update the IsRunning flag
        IsRunning = !glfwWindowShouldClose(m_Window);
    }

    // Destroy the GLFW window and terminate the GLFW library
    void Window::Destroy() {
        glfwDestroyWindow(m_Window);

        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
    // Window callback functions
    void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        GetWindowOf(window)->keyboard->OnKeyCallback(key, scancode, action, mods);
    }

    void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
        GetWindowOf(window)->mouse->cursor_position_callback(xpos, ypos);
    }

    void Window::resize_callback(GLFWwindow* window, int w, int h) {
        GetWindowOf(window)->m_WindowSize = {w,h};
        glViewport(0, 0, w, h);
        // Dispatches the OnWindowResize event to the event receivers
        auto we = DuckEngine::WindowEvent(window, w, h);

        DuckEngine::EventDispatcher::DispatchEvent(&we);
    }

    glm::vec2 Window::GetWindowSize() {
        return m_WindowSize;
    }

    void Window::RenderBackground() const {
        // Set clear color
        glClearColor(background_color.GetR(), background_color.GetG(), background_color.GetB(), background_color.GetA());
        // Clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
} // DuckEngine