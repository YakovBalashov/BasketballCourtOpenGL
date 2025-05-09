#include "../../include/GameObjects/Cube.h"


Cube::Cube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
           const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram,
           const std::shared_ptr<Material>& material) :
    MeshObject(position, rotation, scale, mesh, shaderProgram, material)
{
}
