#include "../../include/GameObjects/ModelObject.h"

void ModelObject::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    shaderProgram->UseProgram();
    shaderProgram->SetMaterial(material);
    model->Render();
    glUseProgram(0);
}
