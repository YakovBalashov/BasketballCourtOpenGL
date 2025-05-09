#pragma once

#include "pgr.h"
#include "Rendering/Mesh.h"

class GameUtils
{
public:
    static float Repeat(float value, float max);

    static std::pair<std::vector<Vertex>, std::vector<GLuint>> GenerateGridLines(
        int divisionsX, int divisionsZ, float spacing, float yLevel);
};
