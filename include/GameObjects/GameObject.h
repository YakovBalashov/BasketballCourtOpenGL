#pragma once
#include "pgr.h"

class GameObject
{
public:
    GameObject() = default;
    
    GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : position(position), rotation(rotation), scale(scale) {}
    
    virtual ~GameObject() = default;

    virtual void Update(float deltaTime) {}

protected:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);  // e.g., Euler angles in degrees
    glm::vec3 scale = glm::vec3(1.0f);
};
