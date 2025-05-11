#pragma once
#include "Interactable.h"
#include "MeshObject.h"

class EnvironmentSwitch : public MeshObject, public Interactable
{
public:
    EnvironmentSwitch(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
                      const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ShaderProgram>& shaderProgram,
                      const std::shared_ptr<Material>& material)
        : MeshObject(position, rotation, scale, mesh, shaderProgram, material)
    {
    }

    void Interact() override;
    
    void Update() override;

private:
    float downTime = 0.2f;
    float currentDownTime = 0.0f;
    bool isDown = false;
    glm::vec3 offset = glm::vec3(0.04f, 0.0f, 0.0f);
};
