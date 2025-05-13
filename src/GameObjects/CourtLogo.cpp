/**
* \file basketball.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Main entry point for the basketball game.
 */

#include "../../include/GameObjects/CourtLogo.h"


void CourtLogo::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    if (!mesh) return;
    shaderProgram->UseProgram();
    shaderProgram->SetMaterial(material);
    shaderProgram->SetTextureOffsetSpeed(glm::vec2(0.3f, 0.0f));
    
    mesh->Render();

    shaderProgram->SetTextureOffsetSpeed(glm::vec2(0.0f, 0.0f));
    
    glUseProgram(0);
}
