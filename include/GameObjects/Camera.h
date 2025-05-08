#pragma once

#include "GameObject.h"
#include "pgr.h"

class Camera : public GameObject
{
public:
    Camera(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : GameObject(position, rotation, scale) {}
    
    glm::mat4 GetViewMatrix() const;

private:
    glm::vec3 vectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
};
