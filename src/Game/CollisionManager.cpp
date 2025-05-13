/**
* \file CollisionManager.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Collision manager for the game.
 */

#include "../../include/Game/CollisionManager.h"

RectangleArea mainArea = RectangleArea(-24.0f, 37.0f, -21.0f, 23.0f);
RectangleArea pocketA = RectangleArea(0.0f, 12.5f, 20.0f, 42.0f);
RectangleArea pocketB = RectangleArea(0.5f, 13.0f, -41.0f, -18.0f);

 std::vector<std::pair<glm::vec3, float>> colliders = {
    {glm::vec3(-6.5f, 0.0f, 0.3f), 1.0f},
    {glm::vec3(20.2f, 0.0f, 0.3f), 1.0f},
     };

bool CollisionManager::isCollidingWithCollider(const std::pair<glm::vec3, float>& collider, const glm::vec3& new_position, float radius)
{
    float distanceX = collider.first.x - new_position.x;
    float distanceZ = collider.first.z - new_position.z;
    float distance = std::sqrt(distanceX * distanceX + distanceZ * distanceZ);
    return distance < (collider.second + radius);
}

bool CollisionManager::IsColliding(glm::vec3 oldPosition, const glm::vec3& newPosition, float objectRadius)
{
    auto isCollidingWithBorders =  !IsInsideRectangle(newPosition, objectRadius, mainArea) &&
        !IsInsideRectangle(newPosition, objectRadius, pocketA) &&
        !IsInsideRectangle(newPosition, objectRadius, pocketB);

    auto isCollidingWithObjects = false;
    for (const auto& collider : colliders)
    {
        if (isCollidingWithCollider(collider, newPosition, objectRadius))
        {
            isCollidingWithObjects = true;
            break;
        }
    }

    return isCollidingWithBorders || isCollidingWithObjects;
}

bool CollisionManager::IsInsideRectangle(const glm::vec3& position, float radius, const RectangleArea& rectangle)
{
    return (position.x - radius >= rectangle.minX() && position.x + radius <= rectangle.maxX() &&
        position.z - radius >= rectangle.minZ() && position.z + radius <= rectangle.maxZ());
}
