#pragma once
#include <GameObjects/GameObject.h>

class CameraObject : public GameObject
{
public:
    CameraObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : GameObject(position, rotation, scale)
    {
    }

    void UpdateOrientation(int mousePositionX, int mousePositionY);

    glm::mat4 GetViewMatrix() const;

private:
    const glm::vec3 vectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
};
