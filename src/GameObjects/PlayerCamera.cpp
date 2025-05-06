#include <GameObjects/PlayerCamera.h>
#include <Game/GameManager.h>

#include "Game/GameUtils.h"

void PlayerCamera::Update()
{
    if (relativeCurrentMovementDirection == glm::vec2(0.0f)) return;
    
    auto currentSpeed = isSprinting ? Player::sprintSpeed : Player::normalSpeed;

    float rotationYRadians = glm::radians(rotation.y);

    glm::vec3 forwardAxis = glm::normalize(glm::vec3(sin(rotationYRadians), 0.0f, cos(rotationYRadians)));
    glm::vec3 rightAxis = glm::normalize(glm::cross(forwardAxis, glm::vec3(0.0f, 1.0f, 0.0f)));

    auto currentMovementDirection = glm::normalize(
        forwardAxis * relativeCurrentMovementDirection.x +
        rightAxis * relativeCurrentMovementDirection.y
    );

    auto newPosition = position + currentMovementDirection * currentSpeed * GameManager::instance->gameInfo.deltaTime;
    if (fabs(newPosition.x) >= Ground::size || fabs(newPosition.z) >= Ground::size) return;
    position = newPosition;
}

void PlayerCamera::UpdateOrientation(int mousePositionX, int mousePositionY)
{
    const float halfWindowHeight = static_cast<float>(GameManager::instance->gameInfo.windowHeight) / 2.0f;
    const float halfWindowWidth = static_cast<float>(GameManager::instance->gameInfo.windowWidth) / 2.0f;

    const float deltaCameraElevationAngle = -Camera::verticalSensitivity * (static_cast<float>(mousePositionY) -
        halfWindowHeight);
    const float deltaCameraAzimuthAngle = -Camera::horizontalSensitivity * (static_cast<float>(mousePositionX) -
        halfWindowWidth);

    if (fabs(rotation.x + deltaCameraElevationAngle) < Camera::maxElevation)
    {
        rotation.x += deltaCameraElevationAngle;
    }

    rotation.y = GameUtils::Repeat(rotation.y + deltaCameraAzimuthAngle, 360.0f);
}

glm::mat4 PlayerCamera::GetViewMatrix() const
{
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

void PlayerCamera::SetMovementDirection(const glm::vec2& direction)
{
    relativeCurrentMovementDirection = direction;
}

void PlayerCamera::StopMovementInDirection(const glm::vec2& direction)
{
    if (relativeCurrentMovementDirection != direction) return;
    relativeCurrentMovementDirection = glm::vec3(0.0f);
}
