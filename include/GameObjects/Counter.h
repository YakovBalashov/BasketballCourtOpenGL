#pragma once
#include "MeshObject.h"

class Counter : public MeshObject
{
public:
    Counter(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
            const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram,
            const std::shared_ptr<Material>& material)
        : MeshObject(position, rotation, scale, mesh, shaderProgram, material)
    {
    }

    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    private:

    int frameCount = 25;
    int currentFrame = 0;
};
