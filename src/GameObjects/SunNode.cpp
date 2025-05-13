/**
* \file SunNode.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief SunNode class that represents a sun object in the game.
 */

#include "../../include/GameObjects/SunNode.h"

#include "Game/GameManager.h"

void SunNode::Update()
{
    auto deltaTime = GameManager::instance->gameInfo.deltaTime;
    float newHeight;
    
    if (isGoingUp)
    {
        newHeight = GetRelativePosition().y + deltaTime * movementSpeed;
        if (newHeight - initialHeight > maxOffset)
        {
            newHeight = initialHeight + maxOffset;
            isGoingUp = false;
        }
    } else
    {
        newHeight = GetRelativePosition().y - deltaTime * movementSpeed;
        if (initialHeight - newHeight > maxOffset)
        {
            newHeight = initialHeight - maxOffset;
            isGoingUp = true;
        }
    }
    SetPosition(glm::vec3(GetRelativePosition().x, newHeight, GetRelativePosition().z));
    SetRotation(glm::vec3(GetRelativeRotation().x + rotationSpeed * deltaTime, GetRelativeRotation().y, GetRelativeRotation().z));
}
