/**
* \file Cube.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Cube class that represents a cube object in the game.
 */

#pragma once
#include "MeshObject.h"

class Cube : public MeshObject
{
public:
    Cube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
               const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram, const std::shared_ptr<Material>& material);
};
