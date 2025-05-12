#include "Rendering/ModelLoader.h"

#include "GameObjects/MeshObject.h"

MeshObject::MeshObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
                       const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram, const std::shared_ptr<Material>& material)
    : RenderableObject(position, rotation, scale, shaderProgram), mesh(mesh), material(material)
{
}

void MeshObject::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    if (!mesh) return;
    shaderProgram->UseProgram();
    shaderProgram->SetMaterial(material);
    mesh->Render();
}
