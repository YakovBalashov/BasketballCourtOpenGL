#include "../../include/GameObjects/Drone.h"

#include "Game/GameUtils.h"
#include <glm/gtx/norm.hpp>

#include "Game/GameManager.h"


Drone::Drone(const glm::vec3& scale, const std::shared_ptr<Model>& model,
             const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<Material>& material,
             const glm::vec3& center, float radius, float cycleDuration):
    ModelObject(glm::vec3(0.0f), glm::vec3(0.0f), scale, model, shader, material), center(center),
    radius(radius), currentAngle(0.0f)
{
    SetPosition(GetCurrentPosition(currentAngle));
    SetRotation(GetCurrentRotation(currentAngle));
    speed = 360.0f / cycleDuration;
}

void Drone::Update()
{
    currentAngle = GameUtils::Repeat(currentAngle + speed * GameManager::instance->gameInfo.deltaTime, 360.0f);
    SetPosition(GetCurrentPosition(currentAngle));
    SetRotation(GetCurrentRotation(currentAngle));
    GameManager::instance->mainShader->UseProgram();
}

glm::vec3 Drone::GetCurrentPosition(float angle) const
{
    return center + glm::vec3(
        radius * cos(glm::radians(angle)),
        center.y,
        radius * sin(glm::radians(angle))
    );
}

glm::vec3 Drone::GetCurrentRotation(float angle) const
{
    float anlgeRadians = glm::radians(currentAngle);

    float directionX = -radius * sin(anlgeRadians);
    float directionY = radius * cos(anlgeRadians);
    
    float yawRadians = std::atan2(directionX, directionY);
    float yaw = glm::degrees(yawRadians);
    
    return glm::vec3(0.0f, yaw, 0.0f);
}
