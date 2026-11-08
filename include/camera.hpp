#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

class Camera {
  public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;

    float movementSpeed = 10.0f;
    float mouseSensitivity = 0.5f;
    float zoomSpeed = 2.0f;

    float fov = 45.0f;
    float aspect = 16.0f / 9.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    void Input(SDL_Event *event);
    void Update(Uint64 deltaTime);

    glm::mat4 GetView();
    glm::mat4 GetProj();
    glm::mat4 GetMVP(glm::mat4 model);
};

#endif
