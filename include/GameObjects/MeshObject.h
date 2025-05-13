/**
* \file MeshObject.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief MeshObject class that represents a 3D object with a mesh and material.
 */

#pragma once
#include "GameObjects/RenderableObject.h"
#include "Rendering/Material.h"
#include "Rendering/Mesh.h"

class MeshObject : public RenderableObject
{
public:
    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    MeshObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
               const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram, const std::shared_ptr<Material>& material);

protected:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
};
