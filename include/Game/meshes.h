/**
* \file meshes.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Mesh data for the game.
 */

#pragma once

#include "pgr.h"
#include "Rendering/Mesh.h"

namespace MeshVertices
{
    extern std::vector<Vertex> cubeVertices;
    extern std::vector<GLuint> cubeIndices;

    extern std::vector<Vertex> squareVertices;
    extern std::vector<GLuint> squareIndices;

    extern std::vector<Vertex> counterVertices;
}
