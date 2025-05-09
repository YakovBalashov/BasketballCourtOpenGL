#include "GameObjects/GameObject.h"

#include "Game/GameUtils.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>      // For glm::pi
#include <glm/gtc/matrix_transform.hpp> // For glm::rotate (if building matrix manually)
#include <glm/gtx/euler_angles.hpp>     // For glm::eulerAngleYXZ, etc.
#include <glm/gtc/quaternion.hpp>       // For glm::qua

void GameObject::AddChild(const std::shared_ptr<GameObject>& child)
{
    children.push_back(child);
    child->SetPosition(child->GetPosition() + position);
    child->SetRotation(child->GetRotation() + rotation);
    child->SetScale(child->GetScale() * scale);
}

void GameObject::SetPosition(const glm::vec3& newPosition)
{
    for (const auto& child : children)
    {
        auto relativePosition = child->GetPosition() - position;
        child->SetPosition(relativePosition + newPosition);
    }

    position = newPosition;
}

void GameObject::SetRotation(const glm::vec3& newRotation)
{
    auto rotationRadians = glm::radians(rotation);
    auto rotationMatrix4x4 = glm::eulerAngleYXZ(rotationRadians.y, rotationRadians.x, rotationRadians.z);
    glm::mat3 rotationMatrix = glm::mat3(rotationMatrix4x4);
    for (const auto& child : children)
    {
        auto relativePosition = child->GetPosition() - position;
        glm::vec3 rotatedPosition = rotationMatrix * relativePosition;
        child->SetPosition(rotatedPosition + position);
    }

    rotation = glm::vec3(GameUtils::Repeat(newRotation.x, 360.0f),
    GameUtils::Repeat(newRotation.y, 360.0f),
    GameUtils::Repeat(newRotation.z, 360.0f));
} 


void GameObject::SetScale(const glm::vec3& newScale)
{
    for (const auto& child : children)
    {
        child->SetScale(child->GetScale() / scale * newScale);
    }
    scale = newScale;
}


