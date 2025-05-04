#include "GameObjects/RenderableObject.h"

void RenderableObject::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    GameUtils::instance->mainShader->UseProgram();
    GameUtils::instance->mainShader->SetPVM(projectionMatrix, viewMatrix, modelMatrix);
    RenderObject(viewMatrix, projectionMatrix);
}
