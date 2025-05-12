#pragma once

#include "pgr.h"
#include "Game/config.h"
#include "GameObjects/RenderableObject.h"

#define millisecondsToSeconds 0.001f

class GameEvents
{
public:
    static void OnRenderDisplay();

    static void OnReshapeWindow(int newWidth, int newHeight);

    static void OnTimer(int);

    static void OnPassiveMouseMotion(int mousePositionX, int mousePositionY);
    
    static glm::vec3 GetMouseRayDirection(int positionX, int positionY);

    static void OnMouseAction(int button, int state, int positionX, int positionY);

    static bool IsPassingTrough(const glm::vec3& mouseRayDirection, const glm::vec3& cameraPosition,
                                const std::vector<std::shared_ptr<GameObject>>::value_type& gameObject);

};
