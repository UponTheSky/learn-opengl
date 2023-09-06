#include <stdexcept>
#include "window.h"
#include "camera.h"

Window* Window::_window = 0;

Window* Window::getInstance() {
  if (_window == nullptr) {
    _window = new Window;
  }
  return _window;
}

Window::Window()
  :
  firstMouse(true),
  deltaTime(0.0f),
  lastFrame(0.0f),
  currentFrame(0.0f),
  _width(WINDOW_WIDTH),
  _height(WINDOW_HEIGHT) {
  // set variables
  lastX = _width / 2;
  lastY = _height / 2;

  // set core objects
  // window setup
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  _glfwWindow = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);

  if (_glfwWindow == nullptr) {
    terminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  // setup callbacks
  glfwMakeContextCurrent(_glfwWindow);
  glfwSetFramebufferSizeCallback(_glfwWindow, framebuffer_size_callback);
  glfwSetCursorPosCallback(_glfwWindow, mouse_callback);
  glfwSetScrollCallback(_glfwWindow, scroll_callback);
  glfwSetInputMode(_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(_glfwWindow);
}

void Window::processInput() {
  Camera* camera = Camera::getInstance();

  if (glfwGetKey(_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(_glfwWindow, true);
  }

  const float cameraSpeed = 2.5f * deltaTime;
  if (glfwGetKey(_glfwWindow, GLFW_KEY_W) == GLFW_PRESS) {
    camera->position += cameraSpeed * camera->front;
  }

  if (glfwGetKey(_glfwWindow, GLFW_KEY_S) == GLFW_PRESS) {
    camera->position -= cameraSpeed * camera->front;
  }

  if (glfwGetKey(_glfwWindow, GLFW_KEY_A) == GLFW_PRESS) {
    camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
  }

  if (glfwGetKey(_glfwWindow, GLFW_KEY_D) == GLFW_PRESS) {
    camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
  }
}

void Window::swapBuffers() {
  glfwSwapBuffers(_glfwWindow);
}

void Window::pollEvents() {
  glfwPollEvents();
}

void Window::terminate() {
  glfwTerminate();
}

double Window::getTime() const {
  return glfwGetTime();
}

inline void framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height) {
  glViewport(0, 0, width, height);
}

inline void mouse_callback(GLFWwindow* glfwWindow, double xpos, double ypos) {
  Window* window = Window::getInstance();
  Camera* camera = Camera::getInstance();

  if (window->firstMouse) {
    window->lastX = xpos;
    window->lastY = ypos;
    window->firstMouse = false;
  }

  float xoffset = xpos - window->lastX;
  float yoffset = window->lastY - ypos;

  window->lastX = xpos;
  window->lastY = ypos;

  const float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  camera->yaw += xoffset;
  camera->pitch += yoffset;

  if (camera->pitch > 89.0f) {
    camera->pitch = 89.0f;
  } else if (camera->pitch < -89.0f) {
    camera->pitch = -89.0f;
  }
}

inline void scroll_callback(GLFWwindow* glfwWindow, double xoffset, double yoffset) {
  Camera* camera = Camera::getInstance();

  camera->fov -= (float)yoffset;

  if (camera->fov < 1.0f) {
    camera->fov = 1.0f;
  } else if (camera->fov > 45.0f) {
    camera->fov = 45.0f;
  }
}
