#pragma once
#include "pgr.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    GameObject() = default;

    GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

    virtual ~GameObject() = default;

    virtual void Update()
    {
    }

    glm::vec3 GetPosition() const;

    glm::quat GetWorldRotation() const;
    
    glm::vec3 GetRotation() const;

    glm::vec3 GetScale() const;

    glm::vec3 GetRelativePosition() const { return position; }

    glm::vec3 GetRelativeRotation() const { return rotation; }

    glm::vec3 GetRelativeScale() const { return scale; }

    void AddChild(const std::shared_ptr<GameObject>& child);

    void SetParent(const std::shared_ptr<GameObject>& newParent);
    

protected:
    void SetPosition(const glm::vec3& newPosition);

    void SetRotation(const glm::vec3& newRotation);

    void SetScale(const glm::vec3& newScale);

private:
    std::vector<std::shared_ptr<GameObject>> children;

    std::shared_ptr<GameObject> parent;
    
    glm::vec3 position = glm::vec3(0.0f);

    glm::vec3 rotation = glm::vec3(0.0f);

    glm::vec3 scale = glm::vec3(1.0f);
};
