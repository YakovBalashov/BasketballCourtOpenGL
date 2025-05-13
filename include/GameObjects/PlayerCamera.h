/**
* \file PlayerCamera.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief PlayerCamera class that represents the camera controlled by the player.
 */

#pragma once
#include "Camera.h"

class PlayerCamera : public Camera
{
public:
    PlayerCamera(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : Camera(position, rotation, scale)
    {
    }

    void Update() override;
    
    void UpdateOrientation(int mousePositionX, int mousePositionY);
    
    void SetMovementDirection(const glm::vec2& direction);

    void StopMovementInDirection(const glm::vec2& direction);

    bool isSprinting = false;
    
private:
    glm::vec2 relativeCurrentMovementDirection = glm::vec3(0.0f, 0.0f, 0.0f);

    float radius = 1.0f;
};
