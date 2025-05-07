#pragma once
#include "Rendering/ShaderProgram.h"
#include "GameObjects/GameObject.h"


class RenderableObject : public GameObject
{
public:
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    void virtual RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
    
    RenderableObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const std::shared_ptr<ShaderProgram>& shaderProgram)
        : GameObject(position, rotation, scale), shaderProgram(shaderProgram)
    {
    }

    protected:
    std::shared_ptr<ShaderProgram> shaderProgram;
};
