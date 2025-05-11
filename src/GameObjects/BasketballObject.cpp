#include "../../include/GameObjects/BasketballObject.h"

#include "Game/GameManager.h"

void BasketballObject::Update()
{
    if (!isBouncing) return;

    float deltaTime = GameManager::instance->gameInfo.deltaTime;

    currentVelocityY += gravity * deltaTime;

    glm::vec3 pos = GetRelativePosition();
    pos.y += currentVelocityY * deltaTime;

    if (pos.y <= minHeight)
    {
        pos.y = minHeight;
        currentVelocityY = -currentVelocityY * bounceDamping;

        if (std::abs(currentVelocityY) < minBounceVelocity)
        {
            isBouncing = false;
            currentVelocityY = 0.0f;
        }
    }
    SetPosition(pos);
}

void BasketballObject::Interact()
{
    if (isBouncing) return;
    isBouncing = true;
    currentVelocityY = initialVelocityY;
}
