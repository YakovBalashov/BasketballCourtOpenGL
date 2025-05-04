#pragma once
#include "GameObjects/RenderableObject.h"
#include "Rendering/Mesh.h"

class MeshObject : public RenderableObject
{
public:
    static std::shared_ptr<Mesh> mesh;

    static void CreateMesh(GLfloat* vertices, unsigned int* indices, int vertexCount, int indexCount);

    static void CreateMeshFromFile(const std::string& path);
    
    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    
    MeshObject() = default;

    MeshObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : RenderableObject(position, rotation, scale) {}
};
