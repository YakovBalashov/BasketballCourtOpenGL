#pragma once
#include "MeshObject.h"
#include "pgr.h"

class CourtLogo : public MeshObject
{
public:
    CourtLogo(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
              const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram,
              const std::shared_ptr<Material>& material)
        : MeshObject(position, rotation, scale, mesh, shaderProgram, material)
    {
    }
    
    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
};
