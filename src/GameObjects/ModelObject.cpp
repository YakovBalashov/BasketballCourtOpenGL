#include "../../include/GameObjects/ModelObject.h"

void ModelObject::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    model->Render();
    glUseProgram(0);
}
