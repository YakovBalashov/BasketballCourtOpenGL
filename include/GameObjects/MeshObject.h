#pragma once
#include "GameObjects/RenderableObject.h"

class MeshObject : public RenderableObject
{
public:
    static void CreateMesh(GLfloat* vertices, unsigned int* indices, int vertexCount, int indexCount);
    static std::shared_ptr<Mesh> mesh;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    MeshObject() = default;
    MeshObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : RenderableObject(position, rotation, scale) {}
};
