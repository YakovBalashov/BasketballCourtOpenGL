#pragma once
#include "pgr.h"

class GameObject
{
public:
    GameObject() = default;

    GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : position(position), rotation(rotation), scale(scale)
    {
    }

    virtual ~GameObject() = default;

    virtual void Update()
    {
    }

    glm::vec3 GetPosition() const { return position; }

    glm::vec3 GetRotation() const { return rotation; }

    glm::vec3 GetScale() const { return scale; }

    void AddChild(const std::shared_ptr<GameObject>& child);
    

protected:
    void SetPosition(const glm::vec3& newPosition);

    void SetRotation(const glm::vec3& newRotation);

    void SetScale(const glm::vec3& newScale);

private:
    std::vector<std::shared_ptr<GameObject>> children;
    
    glm::vec3 position = glm::vec3(0.0f);

    glm::vec3 rotation = glm::vec3(0.0f);

    glm::vec3 scale = glm::vec3(1.0f);
};
