#include "../../include/GameObjects/Camera.h"

glm::mat4 Camera::GetViewMatrix() const
{
    auto rotation = GetRotation();
    auto position = GetPosition();
    
    auto direction = glm::vec3(
        cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y)),
        sin(glm::radians(rotation.x)),
        cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y))
    );
    auto rotationAxis = glm::cross(direction, vectorUp);
    auto rotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), rotationAxis));

    auto rotatedView = rotationMatrix * direction;
    auto rotatedUp = rotationMatrix * vectorUp;

    auto cameraCenter = position + rotatedView;

    return lookAt(position, cameraCenter, rotatedUp);
}
