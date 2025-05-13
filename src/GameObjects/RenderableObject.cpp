/**
* \file RenderableObject.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Base class for all renderable objects in the game.
 */

#include "GameObjects/RenderableObject.h"

void RenderableObject::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    auto position = GetPosition();
    auto rotation = GetRotation();
    auto scale = GetScale();
    
    auto modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, position);

    modelMatrix = glm::scale(modelMatrix, scale);

    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    shaderProgram->UseProgram();
    shaderProgram->SetPVM(projectionMatrix, viewMatrix, modelMatrix);

    RenderObject(viewMatrix, projectionMatrix);
}
