#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include "window.h"
#include "camera.h"

#include "shaders.h"


#include <string>

#include "model.h"

int main()
{
  // window setup
  Window* window = Window::getInstance();
  Camera* camera = Camera::getInstance();

  // shader & model
  Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");
  Model::Model ourModel("backpack/backpack.obj");


  while (!window->shouldClose()) {

    float currentFrame = static_cast<float>(glfwGetTime());
    window->deltaTime = currentFrame - window->lastFrame;
    window->lastFrame = currentFrame;

    window->processInput();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ourShader.use();

        // view/projection transformations
    glm::mat4 projection = camera->getProjection();
    glm::mat4 view = camera->getView();
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    ourShader.setMat4("model", model);
    ourModel.Draw(ourShader);

    // check and call events, and swap the buffers
    window->swapBuffers();
    window->pollEvents();
  }

  glDeleteProgram(ourShader.ID);
  window->terminate();

  return 0;
}
