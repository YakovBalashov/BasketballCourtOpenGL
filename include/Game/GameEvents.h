#pragma once

#include "pgr.h"
#include "Game/data.h"
#include "GameObjects/RenderableObject.h"

class GameEvents
{
public:
    static void DrawWindowContents();

    static void OnRenderDisplay();

    static void OnReshapeWindow(int newWidth, int newHeight);

    static void OnTimer(int);

    static void OnPassiveMouseMotion(int mouseX, int mouseY);

    static void OnKeyPress(unsigned char keyPressed, int mouseX, int mouseY);
};
