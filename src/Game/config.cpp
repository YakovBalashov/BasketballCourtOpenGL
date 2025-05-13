/**
* \file config.cpp
 * \brief Configuration file for the game.
 * \author Yakov Balashov
 * \date Summer Semester 2025 
 */

#include "Game/config.h"

namespace LightsConfig
{
    glm::vec3 sunColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 sunDirection = glm::vec3(0.5f, 1.0f, 0.5f);

    glm::vec3 pointLightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 flashLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 flashLightDirection = glm::vec3(0.1f, -1.0f, 0.0f);
    float flashLightCutOff = glm::cos(glm::radians(30.0f));
}

namespace Fog
{
    glm::vec3 normalColor = glm::vec3(0.5f, 0.5f, 0.5f);
}


