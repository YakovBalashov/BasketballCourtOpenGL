/**
* \file ModelObject.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief ModelObject class that represents a 3D object with a model and material.
 */

#include "../../include/GameObjects/ModelObject.h"

void ModelObject::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    shaderProgram->UseProgram();
    shaderProgram->SetMaterial(material);
    model->Render();
    glUseProgram(0);
}
