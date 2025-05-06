#pragma once
#include "GameObjects/RenderableObject.h"
#include "Rendering/Mesh.h"

class MeshObject : public RenderableObject
{
public:
    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    MeshObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
               const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram);

private:
    std::shared_ptr<Mesh> mesh;
};
