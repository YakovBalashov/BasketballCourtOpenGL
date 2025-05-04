#pragma once

#include "Game/GameUtils.h"
#include "GameObjects/GameObject.h"


class RenderableObject : public GameObject
{
public:
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    void virtual RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;

    RenderableObject() = default;

    RenderableObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : GameObject(position, rotation, scale)
    {
    }
};
