#pragma once
#include <GameObjects/GameObject.h>

class PlayerCamera : public GameObject
{
public:
    PlayerCamera(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : GameObject(position, rotation, scale)
    {
    }

    void Update() override;
    
    void UpdateOrientation(int mousePositionX, int mousePositionY);

    glm::mat4 GetViewMatrix() const;

    void SetMovementDirection(const glm::vec2& direction);

    void StopMovementInDirection(const glm::vec2& direction);

    bool isSprinting = false;
    
private:
    const glm::vec3 vectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec2 relativeCurrentMovementDirection = glm::vec3(0.0f, 0.0f, 0.0f);
};
