#include <GameObjects/CameraObject.h>
#include <Game/GameUtils.h>

void CameraObject::UpdateOrientation(int mousePositionX, int mousePositionY)
{
    const float halfWindowHeight = static_cast<float>(GameUtils::instance->gameInfo.windowHeight) / 2.0f;
    const float halfWindowWidth = static_cast<float>(GameUtils::instance->gameInfo.windowWidth) / 2.0f;

    const float deltaCameraElevationAngle = Camera::verticalSensitivity * (static_cast<float>(mousePositionY) -
        halfWindowHeight);
    const float deltaCameraAzimuthAngle = Camera::horizontalSensitivity * (static_cast<float>(mousePositionX) -
        halfWindowWidth);

    if (fabs(rotation.x + deltaCameraElevationAngle) < Camera::maxElevation)
    {
        // GameUtils::instance->gameInfo.cameraElevationAngle += deltaCameraElevationAngle;
        rotation.x += deltaCameraElevationAngle;
    }

    // GameUtils::instance->gameInfo.cameraAzimuthAngle = fmod(GameUtils::instance->gameInfo.cameraAzimuthAngle + deltaCameraAzimuthAngle, 360.0f);
    rotation.y = fmod(rotation.y + deltaCameraAzimuthAngle, 360.0f);
}

glm::mat4 CameraObject::GetViewMatrix() const
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
