/**
* \file GameUtils.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Utility methods for the game.
 */

#include <Game/GameUtils.h>

#include "Game/GameManager.h"
#include "Game/meshes.h"
#include "Game/paths.h"
#include "GameObjects/MeshObject.h"
#include "Rendering/Texture.h"

float GameUtils::Repeat(float value, float max)
{
    return fmod(fmod(value, max) + max, max);
}

int GameUtils::Repeat(int value, int max)
{
    return static_cast<int>(fmod(fmod(value, max) + max, max));
}


void GameUtils::GenerateGrid(float size, float spacing)
{
    auto redTexture = std::make_shared<Texture>(TexturePaths::red);
    auto gridMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices,
                                            redTexture->getTextureID());

    for (float x = -size; x <= size; x += spacing)
    {
        for (float z = -size; z <= size; z += spacing)
        {
            GameManager::instance->gameObjects.push_back(
                std::make_shared<MeshObject>(glm::vec3(x, 0.1f, z), glm::vec3(0.0f), glm::vec3(0.1f),
                                             gridMesh, GameManager::instance->colorShader,
                                             std::make_shared<Material>()));
        }
    }
}
