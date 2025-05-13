/**
* \file BasketballObject.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Basketball object class.
 */

#pragma once
#include "Interactable.h"
#include "MeshObject.h"
#include "ModelObject.h"

class BasketballObject : public GameObject, public Interactable
{
public:
    BasketballObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : GameObject(position, rotation, scale),
          minHeight(position.y)
    {
    }

    void Update() override;

    void Interact() override;

private:
    bool isBouncing = false;
    float currentVelocityY = 0.0f;
    float bounceDamping = 0.7f;
    float gravity = -9.8f;
    float minBounceVelocity = 0.5f;

    float currentHeight = 0.0f;
    float minHeight;
    float initialVelocityY = 5.0f;
};
