#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"

void Camera::Input(SDL_Event *event) {
    if (event->type == SDL_EVENT_MOUSE_WHEEL) {
        glm::vec3 front = glm::normalize(target - position);
        position += front * event->wheel.y * zoomSpeed;
    } else if (event->type == SDL_EVENT_MOUSE_MOTION) {
        SDL_MouseButtonFlags buttons = SDL_GetMouseState(nullptr, nullptr);
        if (buttons & SDL_BUTTON_RMASK) {
            float xoffset = event->motion.xrel * mouseSensitivity;
            float yoffset = event->motion.yrel * mouseSensitivity;

            yaw += xoffset;
            pitch -= yoffset;

            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }
    }
}
void Camera::Update(Uint64 deltaTime) {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(glm::cross(front, up));

    const bool *keyboardState = SDL_GetKeyboardState(nullptr);
    const float velocity = movementSpeed * (deltaTime / 1000.0f);
    if (keyboardState[SDL_SCANCODE_W]) {
        position += front * velocity;
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        position -= front * velocity;
    }
    if (keyboardState[SDL_SCANCODE_A]) {
        position -= right * velocity;
    }
    if (keyboardState[SDL_SCANCODE_D]) {
        position += right * velocity;
    }

    target = position + front;
}

glm::mat4 Camera::GetView() {
    return glm::lookAt(position, target, up);
}
glm::mat4 Camera::GetProj() {
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}
glm::mat4 Camera::GetMVP(glm::mat4 model) {
    return GetProj() * GetView() * model;
}
