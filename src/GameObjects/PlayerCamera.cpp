#include <GameObjects/PlayerCamera.h>
#include <Game/GameManager.h>

#include "Game/CollisionManager.h"
#include "Game/GameUtils.h"

static float elevationUpperBound = GameUtils::Repeat(CameraConfig::maxElevation, 360.0f);
static float elevationLowerBound = GameUtils::Repeat(-CameraConfig::maxElevation, 360.0f);

void PlayerCamera::Update()
{
    if (relativeCurrentMovementDirection == glm::vec2(0.0f)) return;
    
    auto currentSpeed = isSprinting ? Player::sprintSpeed : Player::normalSpeed;

    float rotationYRadians = glm::radians(GetRotation().y);

    glm::vec3 forwardAxis = glm::normalize(glm::vec3(sin(rotationYRadians), 0.0f, cos(rotationYRadians)));
    glm::vec3 rightAxis = glm::normalize(glm::cross(forwardAxis, glm::vec3(0.0f, 1.0f, 0.0f)));

    auto currentMovementDirection = glm::normalize(
        forwardAxis * relativeCurrentMovementDirection.x +
        rightAxis * relativeCurrentMovementDirection.y
    );

    auto newPosition = GetPosition() + currentMovementDirection * currentSpeed * GameManager::instance->gameInfo.deltaTime;
    // if (fabs(newPosition.x) >= Ground::size || fabs(newPosition.z) >= Ground::size) return;
    if (CollisionManager::IsColliding(GetPosition(), newPosition, radius)) return; 
    SetPosition(newPosition);
}

void PlayerCamera::UpdateOrientation(int mousePositionX, int mousePositionY)
{
    const float halfWindowHeight = static_cast<float>(GameManager::instance->gameInfo.windowHeight) / 2.0f;
    const float halfWindowWidth = static_cast<float>(GameManager::instance->gameInfo.windowWidth) / 2.0f;

    const float deltaCameraElevationAngle = -CameraConfig::verticalSensitivity * (static_cast<float>(mousePositionY) -
        halfWindowHeight);
    const float deltaCameraAzimuthAngle = -CameraConfig::horizontalSensitivity * (static_cast<float>(mousePositionX) -
        halfWindowWidth);


    auto newRotation = GetRotation();
    auto newRotationX = GameUtils::Repeat(newRotation.x + deltaCameraElevationAngle, 360.0f);
    if (newRotationX < elevationUpperBound || newRotationX > elevationLowerBound)
    {
        newRotation.x = newRotationX;
    }
    
    newRotation.y += deltaCameraAzimuthAngle;
    SetRotation(newRotation);
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
