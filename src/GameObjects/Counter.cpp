/**
* \file Counter.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Counter class that displays time left for the attack.
 */

#include "../../include/GameObjects/Counter.h"

#include "Game/GameManager.h"
#include "Game/GameUtils.h"

void Counter::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    currentFrame = static_cast<int>(GameUtils::Repeat(GameManager::instance->gameInfo.currentTime, static_cast<float>(frameCount)));
    
    if (!mesh) return;
    shaderProgram->UseProgram();
    shaderProgram->SetMaterial(material);

    shaderProgram->SetFrameCount(frameCount);
    shaderProgram->SetCurrentFrame(currentFrame);
    
    mesh->Render();
    glUseProgram(0);
}
