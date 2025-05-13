/**
* \file PointLight.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief PointLight class that represents a point light source in the game.
 */

#pragma once
#include "Interactable.h"
#include "MeshObject.h"

class PointLight : public MeshObject, public Interactable
{
public:
    PointLight(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
               const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram,
               const std::shared_ptr<Material>& material, const std::shared_ptr<std::vector<GLuint>>& textureIDs)
        : MeshObject(position, rotation, scale, mesh, shaderProgram, material), 
          textureIDs(textureIDs)
    {
    }

    void Interact() override;

private:
    int currentColor = 0;
    std::vector<glm::vec3> pointLightColors = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
    };

    const std::shared_ptr<std::vector<GLuint>>& textureIDs;
};
