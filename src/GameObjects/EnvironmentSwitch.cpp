#include "../../include/GameObjects/EnvironmentSwitch.h"

#include "Game/GameManager.h"

void EnvironmentSwitch::Interact()
{
    GameManager::instance->skybox->CycleSkybox();
}
