/**
* \file CollisionManager.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Collision manager for the game.
 */

#pragma once
#include "pgr.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Camera.h"

struct RectangleArea
{
    glm::vec4 borders;

    RectangleArea(float minX, float maxX, float minZ, float maxZ)
        : borders(minX, maxX, minZ, maxZ)
    {
    }

    const float& minX() const { return borders.x; }
    const float& maxX() const { return borders.y; }
    const float& minZ() const { return borders.z; }
    const float& maxZ() const { return borders.w; }

    float xMin() const { return minX(); }
    float xMax() const { return maxX(); }
    float zMin() const { return minZ(); }
    float zMax() const { return maxZ(); }
};

class CollisionManager
{
public:
    static bool isCollidingWithCollider(const std::pair<glm::vec3, float>& collider, const glm::vec3& new_position, float radius);
    static bool IsColliding(glm::vec3 oldPosition, const glm::vec3& newPosition, float objectRadius);

private:
    static bool IsInsideRectangle(const glm::vec3& position, float radius, const RectangleArea& rectangle);
};
