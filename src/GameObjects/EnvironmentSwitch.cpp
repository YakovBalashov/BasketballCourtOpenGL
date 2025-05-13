/**
* \file EnvironmentSwitch.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Environment switch class that represents a switch in the game.
 */

#include "../../include/GameObjects/EnvironmentSwitch.h"

#include "Game/GameManager.h"

void EnvironmentSwitch::Interact()
{
    if (isDown) return;
    isDown = true;
    GameManager::instance->skybox->CycleSkybox();
    SetPosition(GetRelativePosition() + offset);
}

void EnvironmentSwitch::Update()
{
    if (!isDown) return;
    currentDownTime -= GameManager::instance->gameInfo.deltaTime;

    if (currentDownTime < 0.0f) 
    {
        currentDownTime = downTime;
        SetPosition(GetRelativePosition() - offset);
        isDown = false;
    }
}
