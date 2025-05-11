#include "../../include/GameObjects/PointLight.h"

#include <iostream>

#include "Game/GameManager.h"
#include "Game/GameUtils.h"


void PointLight::Interact()
{
    currentColor = GameUtils::Repeat(currentColor + 1, static_cast<int>(pointLightColors.size()));

    mesh->SetTexture(textureIDs->at(currentColor));
    
    GameManager::instance->mainShader->UseProgram();
    GameManager::instance->mainShader->SetPointLightColor(pointLightColors[currentColor]);
}
