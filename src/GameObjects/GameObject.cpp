#include "GameObjects/GameObject.h"

#include <iostream>

#include "Game/GameUtils.h"

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/constants.hpp>      
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/euler_angles.hpp>     
#include <glm/gtc/quaternion.hpp>       


GameObject::GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
    this->position = position;
    this->rotation = glm::vec3(GameUtils::Repeat(rotation.x, 360.0f),
                               GameUtils::Repeat(rotation.y, 360.0f),
                               GameUtils::Repeat(rotation.z, 360.0f));
    this->scale = scale;
}

glm::vec3 GameObject::GetPosition() const
{
    if (!parent) return position;
    
    glm::quat parentQuat = glm::quat(glm::radians(parent->GetRotation()));

    auto rotatedPosition = parentQuat * this->position;

    return parent->GetPosition() + rotatedPosition;
}

glm::vec3 GameObject::GetRotation() const
{
    if (!parent) return rotation;

    glm::mat4 localRotMat = glm::eulerAngleYXZ(
        glm::radians(rotation.y),
        glm::radians(rotation.x),
        glm::radians(rotation.z)
    );

    glm::mat4 parentRotMat = glm::eulerAngleYXZ(
        glm::radians(parent->GetRotation().y),
        glm::radians(parent->GetRotation().x),
        glm::radians(parent->GetRotation().z)
    );

    int signX = parent->GetRotation().x < 270.0f && parent->GetRotation().x > 90.0f ? -1 : 1;
    int signY = parent->GetRotation().y < 270.0f && parent->GetRotation().y > 90.0f ? -1 : 1;
    int signZ = parent->GetRotation().z < 270.0f && parent->GetRotation().z > 90.0f ? -1 : 1;

    glm::mat4 worldRotMat = parentRotMat * localRotMat;

    glm::vec3 worldRadians = glm::eulerAngles(glm::quat(worldRotMat));

    glm::vec3 worldEuler = glm::degrees(glm::vec3(worldRadians));

    auto repeated = glm::vec3(
        GameUtils::Repeat(signX * worldEuler.x, 360.0f),
        GameUtils::Repeat(signY * worldEuler.y, 360.0f),
        GameUtils::Repeat(signZ * worldEuler.z, 360.0f)
    );

    return repeated;
}

glm::vec3 GameObject::GetScale() const
{
    if (!parent) return scale;
    return parent->GetScale() * scale;
}

void GameObject::AddChild(const std::shared_ptr<GameObject>& child)
{
    children.push_back(child);
    child->SetParent(shared_from_this());
}

void GameObject::SetParent(const std::shared_ptr<GameObject>& newParent)
{
    this->parent = newParent;
}

void GameObject::SetPosition(const glm::vec3& newPosition)
{
    position = newPosition;
}

void GameObject::SetRotation(const glm::vec3& newRotation)
{
    rotation = glm::vec3(GameUtils::Repeat(newRotation.x, 360.0f),
    GameUtils::Repeat(newRotation.y, 360.0f),
    GameUtils::Repeat(newRotation.z, 360.0f));
} 


void GameObject::SetScale(const glm::vec3& newScale)
{
    scale = newScale;
}


