#include "GameObjects/MeshObject.h"

std::shared_ptr<Mesh> MeshObject::mesh = nullptr;

void MeshObject::CreateMesh(GLfloat* vertices, unsigned int* indices, int vertexCount, int indexCount)
{
    if (mesh) return;
    mesh = std::make_shared<Mesh>(vertices, vertexCount, indices, indexCount);
}

void MeshObject::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    if (!mesh) return;
    mesh->Render();
    glUseProgram(0);
}
