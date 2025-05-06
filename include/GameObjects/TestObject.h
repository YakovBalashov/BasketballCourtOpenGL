#pragma once
#include "GameObjects/MeshObject.h"

class TestObject : public MeshObject
{
public:
    TestObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram)
        : MeshObject(position, rotation, scale, mesh, shaderProgram)
    {
    }
    
    void Update() override;
};
