#pragma once
#include "ModelObject.h"

class SunNode : public ModelObject
{
public:
    SunNode(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
            const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shaderProgram,
            const std::shared_ptr<Material>& material)
        : ModelObject(position, rotation, scale, model, shaderProgram, material), 
          initialHeight(position.y)
    {
    }

    void Update() override;

private:
    float maxOffset = 0.2f;
    float movementSpeed = 0.1f;
    float rotationSpeed = 0.0f;
    float initialHeight;
    bool isGoingUp = true;
};
