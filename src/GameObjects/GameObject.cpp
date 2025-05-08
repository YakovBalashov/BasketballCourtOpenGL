#include "GameObjects/GameObject.h"

#include "Game/GameUtils.h"

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
        child->SetPosition(child->GetPosition() - position + newPosition);
    }

    position = newPosition;
}

void GameObject::SetRotation(const glm::vec3& newRotation)
{
    for (const auto& child : children)
    {
        child->SetRotation(child->GetRotation() - rotation + newRotation);
    }

    rotation = glm::vec3(GameUtils::Repeat(newRotation.x, 360.0f),
                         GameUtils::Repeat(newRotation.y, 360.0f),
                         GameUtils::Repeat(newRotation.z, 360.0f));
}

void GameObject::SetScale(const glm::vec3& newScale)
{
    scale = newScale;

    for (const auto& child : children)
    {
        child->SetScale(child->GetScale() / scale * newScale);
    }
}


