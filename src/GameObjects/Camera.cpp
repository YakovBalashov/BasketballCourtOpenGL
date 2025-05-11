#include "../../include/GameObjects/Camera.h"

glm::mat4 Camera::GetViewMatrix() const
{
    glm::vec3 position = GetPosition();
    glm::vec2 rotation = GetRotation();

    glm::vec3 direction;
    direction.x = cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
    direction.y = sin(glm::radians(rotation.x));
    direction.z = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    direction = glm::normalize(direction);

    glm::vec3 right = glm::normalize(glm::cross(direction, vectorUp));
    glm::vec3 up = glm::normalize(glm::cross(right, direction));

    return glm::lookAt(position, position + direction, up);
}
