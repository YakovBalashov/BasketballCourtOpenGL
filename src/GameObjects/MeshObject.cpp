#include "Rendering/ModelLoader.h"

#include "GameObjects/MeshObject.h"

void MeshObject::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    if (!mesh) return;
    mesh->Render();
    glUseProgram(0);
}

MeshObject::MeshObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
                       const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram)
    : RenderableObject(position, rotation, scale, shaderProgram), mesh(mesh)
{
}
