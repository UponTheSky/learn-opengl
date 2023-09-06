#pragma once

#include <glm/glm.hpp>

static const glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 3.0f);
static const glm::vec3 FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
static const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

// singleton camera class
class Camera {
  public:
    static Camera* getInstance();
    glm::mat4 getView() const;
    glm::mat4 getProjection() const;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float fov;

  private:
    Camera();

    static Camera* _camera;
};
