#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char* WINDOW_TITLE = "Yeatee's OpenGL";

// callbacks
inline void framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height);
inline void mouse_callback(GLFWwindow* glfwWindow, double xpos, double ypos);
inline void scroll_callback(GLFWwindow* glfwWindow, double xoffset, double yoffset);

// singleton
class Window {
  public:
    static Window* getInstance();

    void processInput();
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void terminate();
    double getTime() const;

    // variables
    bool firstMouse;
    float lastX, lastY;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currentFrame = 0.0f;

  private:
    // constructor
    Window();

    // core objects
    static Window* _window; // singleton object
    GLFWwindow* _glfwWindow;

    // variables
    unsigned int _width, _height;
    const char* _title = "OpenGL";
};
