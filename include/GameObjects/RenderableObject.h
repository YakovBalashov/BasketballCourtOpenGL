#pragma once
#include "GameObjects/GameObject.h"
#include "Rendering/Mesh.h"
#include "../core/rendering.h"

class RenderableObject : public GameObject
{
public:
    virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
    {
        auto modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        mainShader->SetPVM(projectionMatrix, viewMatrix, modelMatrix);
    }

    RenderableObject() = default;

    RenderableObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : GameObject(position, rotation, scale)
    {
    }
};
