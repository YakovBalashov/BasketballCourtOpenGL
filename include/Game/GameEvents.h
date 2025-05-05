#pragma once

#include "pgr.h"
#include "Game/config.h"
#include "GameObjects/RenderableObject.h"

class GameEvents
{
public:
    static void OnRenderDisplay();

    static void OnReshapeWindow(int newWidth, int newHeight);

    static void OnTimer(int);

    static void OnPassiveMouseMotion(int mousePositionX, int mousePositionY);

    static void OnKeyPress(unsigned char keyPressed, int mouseX, int mouseY);
};
