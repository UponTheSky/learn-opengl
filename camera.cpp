#include "camera.h"
#include "window.h"
#include <glm/gtc/matrix_transform.hpp>

Camera* Camera::_camera = 0;

Camera* Camera::getInstance() {
  if (_camera == nullptr) {
    _camera = new Camera;
  }
  return _camera;
}

Camera::Camera()
  :
  position(POSITION),
  front(FRONT),
  up(UP),
  yaw(-90.0f),
  pitch(0.0f),
  fov(1.0f) {}

glm::mat4 Camera::getView() const {
  return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjection() const {
  return  glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
}
