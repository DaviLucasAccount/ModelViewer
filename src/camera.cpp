#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"

glm::mat4 Camera::GetView() {
    return glm::lookAt(position, target, up);
}
glm::mat4 Camera::GetProj() {
    float fovy = glm::radians(45.0f);
    float aspect = 640.0f / 360.0f;
    return glm::perspective(fovy, aspect, 0.1f, 100.0f);
}
glm::mat4 Camera::GetMVP(glm::mat4 model) {
    return GetProj() * GetView() * model;
}
