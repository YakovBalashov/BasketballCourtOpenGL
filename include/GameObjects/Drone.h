#pragma once
#include "Camera.h"
#include "ModelObject.h"
#include "Game/GameUtils.h"

class Drone : public ModelObject
{
public:
    Drone(
        const glm::vec3& scale,
        const std::shared_ptr<Model>& model,
        const std::shared_ptr<ShaderProgram>& shader,
        const std::shared_ptr<Material>& material,
        const glm::vec3& center,
        float radius,
        float cycleDuration
    );
    
    void Update() override;

private:
    float currentAngle;
    glm::vec3 center;
    float radius;
    float speed;

    glm::vec3 GetCurrentPosition(float angle) const;

    glm::vec3 GetCurrentRotation(float angle) const;
};
