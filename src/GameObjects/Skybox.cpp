/**
* \file Skybox.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Skybox class that represents a skybox in the game.
 */

#include <GameObjects/Skybox.h>

#include "Game/GameManager.h"
#include "Game/GameUtils.h"

constexpr float skyboxVertices[] = {
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};

constexpr int vertexCount = 36;

Skybox::Skybox(const std::shared_ptr<ShaderProgram>& shaderProgram)
    : RenderableObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), shaderProgram),
      skyboxVAO(0), skyboxVBO(0)
{
    SetupMesh();
    LoadTextures();
}

void Skybox::SetupMesh()
{
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);

    glBindVertexArray(skyboxVAO);

    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));

    glBindVertexArray(0);
}

void Skybox::LoadTextures()
{
    for (const auto& folder : skyboxFolders)
    {
        LoadTexturesFromFolder(folder);
    }
}

void Skybox::LoadTexturesFromFolder(const std::string& folderPath)
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    for (int i = 0; i < skyboxFaceCount; ++i)
    {
        std::string texturePath = folderPath + "/" + std::to_string(i) + ".png";
        pgr::loadTexImage2D(texturePath, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    textureIDs.push_back(textureId);
}


void Skybox::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    glDepthMask(GL_FALSE);

    glm::mat4 skyboxViewMatrix = glm::mat4(glm::mat3(viewMatrix));

    shaderProgram->SetPVM(projectionMatrix, skyboxViewMatrix, glm::mat4(1.0f));
    shaderProgram->SetTextureSampler(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureIDs[currentSkybox]);

    glBindVertexArray(skyboxVAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDepthMask(GL_TRUE);
}

void Skybox::CycleSkybox()
{
    currentSkybox = GameUtils::Repeat(currentSkybox + 1, static_cast<int>(textureIDs.size()));

    auto currentSunParameters = sunParameters[currentSkybox];

    GameManager::instance->mainShader->UseProgram();
    
    GameManager::instance->mainShader->SetSunColorAndIntensity(
        currentSunParameters.color,
        currentSunParameters.ambientIntensity,
        currentSunParameters.diffuseIntensity,
        currentSunParameters.specularIntensity
    );

    auto currentFogParameters = fogParameters[currentSkybox];

    GameManager::instance->mainShader->SetFogParameters(
        currentFogParameters.color,
        currentFogParameters.start,
        currentFogParameters.end
    );
    
}
