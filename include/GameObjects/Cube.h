#pragma once
#include "MeshObject.h"

class Cube : public MeshObject
{
public:
    Cube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
               const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram, const std::shared_ptr<Material>& material);
};
