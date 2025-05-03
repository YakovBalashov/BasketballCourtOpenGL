#pragma once
#include "GameObjects/MeshObject.h"

class TestObject : public MeshObject
{
public:
    TestObject(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f))
        : MeshObject(position, rotation, scale) {}
    
    void Update(float deltaTime) override;
};
