#pragma once

#include "pgr.h"
#include "Rendering/Mesh.h"

class GameUtils
{
public:
    static float Repeat(float value, float max);

    static void GenerateGrid(
        float size, float spacing);
};
